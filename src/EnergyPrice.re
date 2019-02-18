open Css;

open Utils;

let circleStyle =
  style([
    transform(rotate(deg(-90))),
    transformOrigin(pct(50.), pct(50.)),
  ]);

let center =
  style([
    height(pct(100.)),
    display(flexBox),
    alignItems(center),
    justifyContent(center),
  ]);

let circumference = () => 892.21231362;

let calculateDashLength = (total: float, percentage: float) =>
  total /. 100.0 *. percentage;

let circle =
    (dashLength: float, dashGap: float, text: string, subText: string) =>
  <div className=center>
    <svg
      width="300"
      height="300"
      viewBox="0 0 300 300"
      preserveAspectRatio="xMidYMid meet">
      <circle
        className=circleStyle
        cx="150"
        cy="150"
        r="142"
        fill="none"
        stroke="#e6e6e6"
        strokeWidth="16"
      />
      <circle
        className=circleStyle
        cx="150"
        cy="150"
        r="142"
        fill="none"
        stroke="#02C39A"
        strokeWidth="16"
        strokeDasharray=(
          string_of_float(dashLength) ++ "," ++ string_of_float(dashGap)
        )
      />
      <text
        x="50%"
        y="50%"
        textAnchor="middle"
        fontSize="4rem"
        fill="#FDFDF9"
        fontFamily="Open Sans"
        fontWeight="400"
        dy=".3em">
        (ReasonReact.string(text))
      </text>
      <text
        x="50%"
        y="65%"
        textAnchor="middle"
        fontSize="2rem"
        fill="#FDFDF9"
        fontFamily="Open Sans"
        fontWeight="400"
        dy=".3em">
        (ReasonReact.string(subText))
      </text>
    </svg>
  </div>;

let renderCircle = (text: string, subText: string, startsAt: string) => {
  let startsAtInMilliSeconds = startsAt |> toMilliseconds;
  let percentageUsed = (currentTime() -. startsAtInMilliSeconds) /. 3600000.;
  let dashLength =
    calculateDashLength(circumference(), percentageUsed *. 100.0);
  circle(dashLength, circumference(), text, subText);
};

let component = ReasonReact.statelessComponent("EnergyPrice");

let make = (~text, ~subText, ~startsAt, _children) => {
  ...component,
  render: _self => renderCircle(text, subText, startsAt),
};