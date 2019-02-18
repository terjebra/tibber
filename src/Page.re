open Css;

/*No template ares so must give specific placement*/
let grid =
  style([
    display(grid),
    height(vh(100.)),
    gridTemplateColumns([fr(1.0)]),
    gridTemplateRows([px(100), fr(1.0), auto]),
    media(
      "only screen and (min-width :  35em)",
      [
        gridTemplateColumns([px(100), fr(1.0), fr(1.0)]),
        gridTemplateRows([auto, fr(1.0)]),
        gridRowGap(px(0)),
      ],
    ),
  ]);

let header =
  style([
    gridColumnStart(1),
    gridColumnEnd(-1),
    gridRowStart(1),
    gridRowEnd(2),
    media(
      "only screen and (min-width : 35em)",
      [
        gridColumnStart(1),
        gridColumnEnd(-1),
        gridRowStart(1),
        gridRowEnd(2),
      ],
    ),
  ]);

let menu =
  style([
    gridColumnStart(1),
    gridColumnEnd(-1),
    gridRowStart(3),
    gridRowEnd(-1),
    boxShadow(
      ~x=px(0),
      ~y=px(5),
      ~blur=px(2),
      ~spread=px(6),
      rgba(0, 0, 0, 0.14),
    ),
    media(
      "only screen and (min-width : 35em)",
      [
        boxShadow(
          ~x=px(4),
          ~y=px(0),
          ~blur=px(2),
          ~spread=px(-1),
          rgba(0, 0, 0, 0.14),
        ),
        gridColumnStart(1),
        gridColumnEnd(2),
        gridRowStart(2),
        gridRowEnd(-1),
      ],
    ),
  ]);

let content =
  style([
    padding4(em(0.5), em(1.5), em(0.5), em(1.5)),
    gridColumnStart(1),
    gridColumnEnd(-1),
    gridRowStart(2),
    gridRowEnd(3),
    media(
      "only screen and (min-width : 35em)",
      [
        gridColumnStart(2),
        gridColumnEnd(-1),
        gridRowStart(2),
        gridRowEnd(3),
      ],
    ),
  ]);

let component = ReasonReact.statelessComponent("Page");

let make = _children => {
  ...component,
  render: _self =>
    <div className=grid>
      <div className=header> <Header title="Tibber metrics" /> </div>
      <main className=content> <Main /> </main>
      <div className=menu> <Navbar /> </div>
    </div>,
};