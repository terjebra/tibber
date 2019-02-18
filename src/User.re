open Css;

/* Create a GraphQL Query by using the graphql_ppx */
module GetViewer = [%graphql
  {|
  query GetViewer{
    viewer {
      login
      name
      homes {
        appNickname
        meteringPointData{
          estimatedAnnualConsumption
        }
        currentSubscription {
          status
          priceInfo {
            current {
              total
              energy
              tax
              startsAt
            }
          }
        }
      }
    }
  }
|}
];

let circleStyle =
  style([
    transform(rotate(deg(-90))),
    transformOrigin(pct(50.), pct(50.)),
  ]);

let center =
  style([display(flexBox), alignItems(center), justifyContent(center)]);

module GetViewerQuery = ReasonApollo.CreateQuery(GetViewer);

let circumference = () => 452.389342117;

let component = ReasonReact.statelessComponent("User");

let currentTime = () => Js.Date.now();

let diffTime = (currentTime: float, time: float) => currentTime -. time;

let toMilliseconds = (date: string) =>
  Js.Date.fromString(date) |> Js.Date.getTime;

let calculateDashLength = (total: float, percentage: float) =>
  total /. 100.0 *. percentage;

let circle = (dashLength: float, dashGap: float, totalCost: float) =>
  <div className=center>
    <svg
      width="160"
      height="160"
      viewBox="0 0 160 160"
      preserveAspectRatio="xMidYMid meet">
      <circle
        className=circleStyle
        cx="80"
        cy="80"
        r="72"
        fill="none"
        stroke="#e6e6e6"
        strokeWidth="16"
      />
      <circle
        className=circleStyle
        cx="80"
        cy="80"
        r="72"
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
        stroke="#FDFDF9"
        fontSize="10 px"
        fontFamily="Open Sans"
        fontWeight="200"
        dy=".3em">
        (ReasonReact.string(string_of_float(totalCost *. 100.)))
      </text>
    </svg>
    <svg
      width="160"
      height="160"
      viewBox="0 0 160 160"
      preserveAspectRatio="xMidYMid meet">
      <circle
        className=circleStyle
        cx="80"
        cy="80"
        r="72"
        fill="none"
        stroke="#e6e6e6"
        strokeWidth="16"
      />
      <circle
        className=circleStyle
        cx="80"
        cy="80"
        r="72"
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
        stroke="#FDFDF9"
        fontSize="10 px"
        fontFamily="Open Sans"
        fontWeight="200"
        dy=".3em">
        (ReasonReact.string(string_of_float(totalCost *. 100.)))
      </text>
    </svg>
  </div>;

let renderCircle = (totalCost: float, startsAt: string) => {
  let startsAtInMilliSeconds = startsAt |> toMilliseconds;
  Js.Console.log(startsAtInMilliSeconds);
  Js.Console.log(currentTime());
  let percentageUsed = (currentTime() -. startsAtInMilliSeconds) /. 3600000.;
  Js.Console.log(percentageUsed);
  let dashLength =
    calculateDashLength(circumference(), percentageUsed *. 100.0);
  circle(dashLength, circumference(), totalCost);
};

let renderCurrentPrice = current =>
  switch (current##total, current##startsAt) {
  | (Some(total), Some(startsAt)) => renderCircle(total, startsAt)
  | (_, _) => <div />
  };

let renderPrice = priceInfo =>
  switch (priceInfo##current) {
  | Some(current) => <div> (renderCurrentPrice(current)) </div>
  | None => <div />
  };

let renderPriceInfo = currentSubscription =>
  switch (currentSubscription##priceInfo) {
  | Some(priceInfo) => <div> (renderPrice(priceInfo)) </div>
  | None => <div />
  };

let renderCurrentSubscription = home =>
  switch (home##currentSubscription) {
  | Some(currentSubscription) =>
    <div> (renderPriceInfo(currentSubscription)) </div>
  | None => <div />
  };

let renderEstimatedAnnualConsumption = meteringPointData =>
  switch (meteringPointData##estimatedAnnualConsumption) {
  | Some(estimatedAnnualConsumption) =>
    <div>
      (ReasonReact.string(string_of_int(estimatedAnnualConsumption)))
    </div>
  | None => <div />
  };

let renderMeteringPoint = home =>
  switch (home##meteringPointData) {
  | Some(meteringPointData) =>
    <div> (renderEstimatedAnnualConsumption(meteringPointData)) </div>
  | None => <div />
  };

let renderNickName = home =>
  switch (home##appNickname) {
  | Some(appNickname) => <div> (ReasonReact.string(appNickname)) </div>
  | None => <div />
  };

let renderHome = home =>
  switch (home) {
  | Some(value) =>
    <div>
      (renderNickName(value))
      (renderMeteringPoint(value))
      (renderCurrentSubscription(value))
    </div>
  | None => <div />
  };

let make = _children => {
  ...component,
  render: _self =>
    <GetViewerQuery>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(error) =>
               <div> (ReasonReact.string(error##message)) </div>
             | Data(response) =>
               <div>
                 <div>
                   (
                     ReasonReact.string(
                       switch (response##viewer##name) {
                       | Some(name) => name
                       | None => ""
                       },
                     )
                   )
                 </div>
                 <div>
                   (
                     response##viewer##homes
                     |> Js.Array.map(home => renderHome(home))
                     |> ReasonReact.array
                   )
                 </div>
               </div>
             }
         )
    </GetViewerQuery>,
};