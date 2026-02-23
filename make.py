#!/usr/bin/env python3

import os
import platform
import re
import subprocess
import sys
import time
from argparse import ArgumentParser
from dataclasses import dataclass
from pathlib import Path
from typing import Any

EXT_WHITELIST = [".cpp", ".c", ".typ", ".txt", ".bash"]
PLATFORM_TYPST = {
    "Windows": "typst-windows.exe",
    "Linux": "typst-linux",
}

IGNORE_FOLDERS = ["pdfs"]

NEWLINE = "\n"

base_path = Path(__file__).parent

conf: "Conf"


def section_name(raw: str) -> str | None:
    if raw.startswith("."):
        return None
    return " ".join(w.capitalize() for w in raw.split())


def file_name(name: str) -> str | None:
    for ext in EXT_WHITELIST:
        if name.endswith(ext):
            name = name.removesuffix(ext)
            name = re.split(r"[-_\s]+", name)
            return " ".join(w.lower() for w in name)
    return None


def file_contents(filename: str, raw: str) -> str:
    if filename.endswith(".typ"):
        return Verbatim("[\n" + raw.strip() + "\n]")

    # remove empty lines for cpp files
    if filename.endswith(".cpp"):
        raw = "\n".join(line for line in raw.splitlines() if line.strip())

    extension = ""
    if "." in filename:
        extension = filename.split(".")[-1]
    return Verbatim("```" + extension + "\n" + raw.strip() + "\n```")


class Verbatim(str):
    pass


def serialize(val: Any) -> str:
    if isinstance(val, Verbatim):
        return val
    if isinstance(val, bool):
        return "true" if val else "false"
    if isinstance(val, float) or isinstance(val, int):
        return str(val)
    if isinstance(val, str):
        return '"' + val.replace("\\", "\\\\").replace('"', '\\"') + '"'
    if isinstance(val, list) or isinstance(val, tuple):
        return "(" + "".join(serialize(subval) + "," for subval in val) + ")"
    if not isinstance(val, dict):
        val = {
            attrname: getattr(val, attrname)
            for attrname in dir(val)
            if not attrname.startswith("_")
        }
    if not val:
        return "(:)"
    for k in val:
        if not isinstance(k, str):
            raise RuntimeError("dictionary key must be a string")
    return (
        "(" + ",".join(serialize(k) + ":" + serialize(v) for k, v in val.items()) + ")"
    )


def compose(sections: list[tuple[str, list[tuple[str, str]]]]) -> str:
    args = {
        "conf": conf,
        "content": sections,
    }
    return f"""
#import "template.typ": compose
#compose({serialize(args)})
    """


def ingest() -> list[tuple[str, list[tuple[str, str]]]]:
    sections = []
    for dirname in os.listdir(base_path):
        if dirname in IGNORE_FOLDERS:
            continue
        dir = base_path.joinpath(dirname)
        if dir.is_dir():
            secname = section_name(dirname)
            if secname is not None:
                sec = []
                for filename in os.listdir(dir):
                    fname = file_name(filename)
                    if fname is not None:
                        filepath = dir.joinpath(filename)
                        txt = filepath.read_text()
                        sec.append((fname, file_contents(filename, txt)))
                sections.append((secname, sec))
    return sections


def compile(src: str):
    if conf.print_source:
        print(
            "printing source code instead of compiling because --print-source flag was received",
            file=sys.stderr,
        )
        print("typst source code:", file=sys.stderr)
        print(src)
    else:
        system = platform.system()
        exe_name = PLATFORM_TYPST.get(system)
        if exe_name is None:
            raise RuntimeError(f"typst binary not available for platform '{system}'")
        typst_dir = base_path.joinpath(".typst")
        exe_path = typst_dir.joinpath(exe_name)
        out_path = base_path.joinpath(conf.out)

        # Check if binary exists
        if not exe_path.exists():
            raise RuntimeError(f"Typst binary not found at {exe_path}")

        subprocess.run(
            [
                exe_path,
                "compile",
                "--root",
                typst_dir,
                "--format",
                "pdf",
                "-",
                out_path,
            ],
            input=src.encode("utf-8"),
        )
        print(f"wrote pdf to {conf.out}", file=sys.stderr)


def merge_pdfs_linux(main_pdf: Path, pdf_folder: Path):
    if not pdf_folder.exists():
        print("folder 'pdfs/' not found, skipping merge", file=sys.stderr)
        return
    pdf_files = sorted(pdf_folder.glob("*.pdf"))
    if not pdf_files:
        print("no PDFs in 'pdfs/', nothing to add", file=sys.stderr)
        return
    print(
        f"adding {len(pdf_files)} PDFs from '{pdf_folder}' to the end of the document",
        file=sys.stderr,
    )

    temp_pdf = main_pdf.with_name("notebook_temp.pdf")
    merged_pdf = main_pdf.with_name("notebook.pdf")

    files_to_merge = [str(main_pdf)] + [str(pdf) for pdf in pdf_files]

    try:
        subprocess.run(["pdfunite", *files_to_merge, str(temp_pdf)], check=True)
        temp_pdf.replace(merged_pdf)
        print(f"Merged PDF generated at: {merged_pdf}", file=sys.stderr)
    except FileNotFoundError:
        print(
            "⚠️ 'pdfunite' not found. Install it with 'sudo apt install poppler-utils' or 'sudo pacman -S poppler'",
            file=sys.stderr,
        )
    except subprocess.CalledProcessError as e:
        print(f"⚠️ Error merging PDFs: {e}", file=sys.stderr)


@dataclass
class Conf:
    out: str
    university: str
    team: str
    print_source: bool
    column_count: int
    column_gutter: Verbatim
    margin: Verbatim
    paper: str
    portrait: bool
    theme: str
    no_index: bool
    no_cover: bool
    no_pdfs: bool
    font_size: Verbatim
    section_font_size: Verbatim
    filename_font_size: Verbatim
    math_font_size: Verbatim
    math_section_text_font_size: Verbatim
    margin_top: Verbatim
    margin_bottom: Verbatim
    margin_left: Verbatim
    margin_right: Verbatim

    @staticmethod
    def parse() -> "Conf":
        p = ArgumentParser(
            description="Make a competitive programming notebook from source files"
        )
        p.add_argument("-o", "--out", required=True, help="Output file path")
        p.add_argument(
            "--print-source",
            action="store_true",
            help="Print Typst source instead of compiling a PDF",
        )
        p.add_argument(
            "-u", "--university", default="<university>", help="University name"
        )
        p.add_argument("-t", "--team", default="<team>", help="Team name")
        p.add_argument(
            "--font-size", default="6.984pt", help="Size of the font used for code"
        )
        p.add_argument("--column-count", default="3", help="Number of columns")
        p.add_argument("--column-gutter", default="5mm", help="Space between columns")
        p.add_argument(
            "--margin", default="10mm", help="Page margin (default for all sides)"
        )
        p.add_argument("--margin-top", default=None, help="Top margin")
        p.add_argument("--margin-bottom", default=None, help="Bottom margin")
        p.add_argument("--margin-left", default=None, help="Left margin")
        p.add_argument("--margin-right", default=None, help="Right margin")

        p.add_argument("--paper", default="a4", help="Page paper size")
        p.add_argument("--theme", default="", help="Code highlighting theme")
        p.add_argument(
            "--portrait", action="store_true", help="Whether to orient in portrait mode"
        )
        p.add_argument(
            "--no-index", action="store_true", help="Do not print the table of contents"
        )
        p.add_argument(
            "--no-cover",
            action="store_true",
            help="Do not print the cover (title/team)",
        )
        p.add_argument(
            "--no-pdfs",
            action="store_true",
            help="Do not merge PDFs from the pdfs folder",
        )
        p.add_argument(
            "--filename-font-size",
            default="10pt",
            help="Font size for file names (e.g., 12pt)",
        )
        p.add_argument(
            "--section-font-size",
            default="12pt",
            help="Font size for section/folder titles (e.g., 12pt)",
        )
        p.add_argument(
            "--math-font-size",
            default="11pt",
            help="Font size for math formulas (e.g., 11pt)",
        )
        p.add_argument(
            "--math-section-text-font-size",
            default="11pt",
            help="Font size for text content in math sections (e.g., 11pt)",
        )

        args = sys.argv[1:]
        confpath = base_path.joinpath("makeconf")
        if confpath.is_file():
            extra = confpath.read_text().splitlines()
            args = extra + args
        parsed = p.parse_args(args)

        if parsed.margin_top is None:
            parsed.margin_top = parsed.margin
        if parsed.margin_bottom is None:
            parsed.margin_bottom = parsed.margin
        if parsed.margin_left is None:
            parsed.margin_left = parsed.margin
        if parsed.margin_right is None:
            parsed.margin_right = parsed.margin

        attrs = {}
        for name, ty in Conf.__annotations__.items():
            attrs[name] = ty(getattr(parsed, name))

        for attrname in dir(parsed):
            if not attrname.startswith("_") and attrname not in Conf.__annotations__:
                raise NameError(f"unknown commandline attribute '{attrname}'")
        return Conf(**attrs)


def main():
    global conf
    start = time.monotonic()
    conf = Conf.parse()
    print("processing input files", file=sys.stderr)
    sections = ingest()
    src = compose(sections)
    print("compiling to pdf", file=sys.stderr)

    compile(src)

    if not conf.no_pdfs:
        merge_pdfs_linux(base_path.joinpath(conf.out), base_path.joinpath("pdfs"))
    else:
        print("skipping PDF merge because --no-pdfs flag was received", file=sys.stderr)

    print(f"done in {time.monotonic() - start:.2f}s", file=sys.stderr)


if __name__ == "__main__":
    main()
