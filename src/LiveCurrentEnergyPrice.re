open Utils;

type action =
  | Tick;

type state = {
  ticks: float,
  endTime: float,
};

let component = ReasonReact.reducerComponent("LiveCurrentEnergyPrice");

let make = (~onPriceElapsed, ~text, ~subText, ~startsAt, _children) => {
  ...component,
  initialState: () => {
    ticks: toMilliseconds(startsAt),
    endTime: endTimeInMilliseconds(startsAt),
  },
  reducer: (action, state) =>
    switch (action) {
    | Tick =>
      ReasonReact.UpdateWithSideEffects(
        {
          ticks: state.ticks +. 1000.,
          endTime: endTimeInMilliseconds(startsAt),
        },
        (
          _self => {
            let timeLeft = diffTime(state.endTime, state.ticks);
            if (timeLeft == 0.) {
              onPriceElapsed();
            };
          }
        ),
      )
    },
  didMount: self => {
    let intervalId = Js.Global.setInterval(() => self.send(Tick), 1000);
    self.onUnmount(() => Js.Global.clearInterval(intervalId));
  },
  render: (_) => <EnergyPrice text subText startsAt />,
};