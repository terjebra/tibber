open Css;

let steps = style([listStyleType(none), paddingLeft(em(0.5))]);

let step = style([marginBottom(em(0.5))]);

let stepCircle =
  style([
    borderRadius(pct(50.)),
    border(px(1), solid, hex("FDFDF9")),
    height(em(2.)),
    width(em(2.)),
    display(flexBox),
    justifyContent(center),
    alignItems(center),
    backgroundColor(hsla(167, 98, 39, 1.)),
  ]);

let content =
  style([
    display(flexBox),
    alignItems(center),
    children([marginLeft(em(0.2))]),
    flexWrap(wrap),
  ]);

let actions =
  style([position(absolute), bottom(em(0.4)), right(em(0.4))]);

type state = string;

type action =
  | Token(string);

let component = ReasonReact.reducerComponent("Welcome");

let make = (~onRegisterClicked, _children) => {
  ...component,
  initialState: () => "",
  reducer: (action, _state) =>
    switch (action) {
    | Token(text) => Update(text)
    },
  render: ({state, send}) =>
    <Modal>
      <h1> (ReasonReact.string("Welcome")) </h1>
      <p>
        (ReasonReact.string("In order to use this app, an active "))
        <a href="https://norge.tibber.com/">
          (ReasonReact.string("tibber-subscription"))
        </a>
        (ReasonReact.string(" is required "))
      </p>
      <h3> (ReasonReact.string("How to use")) </h3>
      <ul className=steps>
        <li className=step>
          <div className=content>
            <span className=stepCircle> (ReasonReact.string("1")) </span>
            <span>
              (ReasonReact.string("Obtain token at "))
              <a href="https://developer.tibber.com/settings/accesstoken">
                (ReasonReact.string("the developer site"))
              </a>
            </span>
          </div>
        </li>
        <li className=step>
          <div className=content>
            <div className=stepCircle> (ReasonReact.string("2")) </div>
            <span> (ReasonReact.string("Copy the token")) </span>
          </div>
        </li>
        <li className=step>
          <div className=content>
            <div className=stepCircle> (ReasonReact.string("3")) </div>
            <span> (ReasonReact.string("Register token:")) </span>
            <Input value=state inputChanged=(text => Token(text) |> send) />
          </div>
        </li>
      </ul>
      <div className=actions>
        <Button text="Register" onClick=((_) => onRegisterClicked(state)) />
      </div>
    </Modal>,
};