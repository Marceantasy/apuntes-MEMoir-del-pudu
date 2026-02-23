#let compose(
  args,
) = {
  // Document config
  let conf = args.conf

  set page(
        flipped: not conf.portrait,
        margin: (
          top: conf.margin_top,
          bottom: conf.margin_bottom,
          left: conf.margin_left,
          right: conf.margin_right
        ),
        paper: conf.paper
      )

  set text(font: "Roboto")

  show raw: set text(font: "Fira Code", weight: 500, size: conf.font_size)

  set raw(theme: "themes/"+conf.theme+".tmTheme") if conf.theme != ""

  // Title
  if not conf.no_cover {
    align(center, {
      text(size: 10mm)[Team Notebook]
      v(-3mm)
      text(size: 6mm, conf.university + " - " + conf.team)
    })
  }

  // Index
  if not conf.no_index {
    place(columns(conf.column_count, gutter: conf.column_gutter, {
      for i in range(conf.column_count - 1) {
        colbreak()
        align(left+top, move(line(angle: 90deg, length: 164mm), dx: -conf.column_gutter/2))
      }
    }))
    columns(conf.column_count, gutter: conf.column_gutter, {
      show outline.entry.where(level: 1): set text(weight: "bold")
      outline(title: none, indent: 5mm)
    })

    pagebreak(weak: true)
  }

  // Body setup

  set page(header: {
    align(left, move(conf.university + " - " + conf.team, dy: 100%))
    align(right, move(counter(page).display()))
  })

  show: columns.with(conf.column_count, gutter: conf.column_gutter)

  set heading(numbering: "1.1")

  show heading.where(level: 1): set text(size: conf.section_font_size)
  show heading.where(level: 1): set block(below: 0.5em)

  show heading.where(level: 2): set text(size: conf.filename_font_size)

  // Set default font size for math content
  show math.equation: set text(size: conf.math_font_size)

  let codeblock(title, code) = [
    == #title

    #block(
      {
        set text(size: conf.math_section_text_font_size)
        code
      },
      stroke: 1pt,
      radius: 1mm,
      width: 100%,
      outset: 1.5mm,
      breakable: true,
    )
  ]

  // Body contents
  for (sname, blocks) in args.content [
    = #sname

    #for (title, code) in blocks {
      codeblock(title, code)
    }
  ]
}
