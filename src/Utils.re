let currentTime = () => Js.Date.now();

let diffTime = (currentTime: float, time: float) => currentTime -. time;

let toMilliseconds = (date: string) =>
  Js.Date.fromString(date) |> Js.Date.getTime;

let endTimeInMilliseconds = (date: string) =>
  toMilliseconds(date) +. 3600000.;