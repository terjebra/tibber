# Tibber

A reasonml journey to experiment and learn the language.
<Snackbar message=Error(error##message) />;

- Context api
- Typed CSS
- GraphQL
- Parcel

# About

The app uses the Tibber [graphql api](https://developer.tibber.com/) to get the current kwh cost.

## Development

## Generate schema

```sh
yarn send-introspection-query https://api.tibber.com/v1-beta/gql

```

## Run project

```sh
yarn install
yarn start
yarn parcel build index.html  (copy fonts)
yarn parcel index.html
```

## Usage

When the app starts it prompts for an api-token, that may be obtained at [Tibber's developer site](https://developer.tibber.com/settings/accesstoken). Currently only the query is supported.

## Color scheme

Colorsfrom [Coolors](https://coolors.co/05668d-028090-00a896-02c39a-f0f3bd)
