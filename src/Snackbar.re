open Css;

open AppContext;

open Utils;

let component = ReasonReact.statelessComponent("Snackbar");

let baseContainer =
  style([
    position(fixed),
    bottom(em(1.)),
    left(em(1.)),
    padding2(em(1.), em(1.)),
    borderRadius(px(5))
  ]);

let showContainer = (message: message) =>
  style([
    visibility(visible),
    backgroundColor(
      switch (message) {
      | Information(_message) => hsla(167, 98, 39, 1.)
      | Error(_message) => hsla(7, 98, 39, 1.)
      },
    ),
  ]);

let styles = (message: option(message)) => {
  switch (message) {
    | Some(message) =>
        merge([baseContainer, showContainer(message)])
    | None =>
       merge([baseContainer, style([visibility(hidden)])])
  }
};

let content = style([display(flexBox), justifyContent(center)]);

let make = (~message:option(message), _children) => {
  ...component,
  render: _self =>
  
    <div className=styles(message)>
      <div className=content>
        (
          switch (message) {
          | Some(message) =>
            switch (message) {
            | Information(message) => ReasonReact.string(message)
            | Error(message) => ReasonReact.string(message)
            }
          | None => ReasonReact.string("")
          }
        )
      </div>
    </div>,
};