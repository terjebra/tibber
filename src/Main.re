type route =
  | CurrentEnergyPriceRoute
  | HomesRoute
  | SettingsRoute;

type state = {route};

type action =
  | ChangeRoute(route);

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => CurrentEnergyPriceRoute
  | ["current-energy-price"] => CurrentEnergyPriceRoute
  | ["homes"] => HomesRoute
  | ["settings"] => SettingsRoute
  | _ => CurrentEnergyPriceRoute
  };

let component = ReasonReact.reducerComponent("Main");

let make = _children => {
  ...component,
  reducer: (action, _state) =>
    switch (action) {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    },
  initialState: () => {route: CurrentEnergyPriceRoute},
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self =>
    switch (self.state.route) {
    | CurrentEnergyPriceRoute => <CurrentEnergyPrice />
    | HomesRoute => <Homes />
    | SettingsRoute => <Settings />
    | _ => <CurrentEnergyPrice />
    },
};