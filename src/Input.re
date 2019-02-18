open Css;

let input =
  style([
    fontSize(inherit_),
    border(px(2), solid, hex("ccc")),
    borderRadius(px(5)),
    marginTop(em(0.2)),
    width(pct(80.)),
  ]);

let component = ReasonReact.statelessComponent("Input");

let make = (~inputChanged, ~value, _children) => {
  ...component,
  render: _self =>
    <input
      className=input
      value
      onChange=(
        event => {
          let text = ReactEvent.Form.target(event)##value;
          inputChanged(text);
        }
      )
    />,
};