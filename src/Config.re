module Config = {
  [@bs.val] external apiUrlVariable : string = "process.env.API_URL";
  type config = {apiUrl: string};
  let getConfig = () : config => {apiUrl: apiUrlVariable};
};