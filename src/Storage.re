let tokenKey = "token";

let getToken = () => Dom_storage.(localStorage |> getItem(tokenKey));

let saveToken = (token: string) =>
  Dom_storage.(localStorage |> setItem(tokenKey, token));