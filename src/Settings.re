open AppContext;

open Css;

type state = string;

type action =
  | Text(string);

let component = ReasonReact.reducerComponent("Settings");

let area =
  style([
    display(flexBox),
    alignItems(center),
    children([marginRight(em(0.9))]),
    flexWrap(wrap),
  ]);

let make = (_) => {
  ...component,
  initialState: () => "",
  reducer: (action, _state) =>
    switch (action) {
    | Text(text) => Update(text)
    },
  render: ({state, send}) =>
    <AppContext.Consumer>
      ...(
           context => {
             let getvalue = () =>
               if (String.length(state) == 0) {
                 switch (context.token) {
                 | Some(token) => token
                 | None => ""
                 };
               } else {
                 state;
               };
             <div className=area>
               <div> (ReasonReact.string("Token")) </div>
               <Input
                 value=(getvalue())
                 inputChanged=(text => Text(text) |> send)
               />
               <Button
                 text="Save"
                 onClick=((_) => context.updateToken(getvalue()))
               />
             </div>;
           }
         )
    </AppContext.Consumer>,
};