open Css;

let appNav =
  style([
    display(flexBox),
    flexDirection(row),
    justifyContent(spaceAround),
    media("only screen and (min-width: 35em)", [flexDirection(column)]),
    listStyleType(none),
    paddingLeft(em(0.0)),
  ]);

let appNavItem = style([marginTop(em(0.5))]);

let navbarItem =
  style([SVG.fill(hex("FDFDF9")), margin(auto), display(block)]);

let component = ReasonReact.statelessComponent("Navbar");

let make = _children => {
  ...component,
  render: _self =>
    <nav>
      <ul className=appNav>
        <li className=appNavItem>
          <Link href="/homes">
            <svg
              width="50" height="50" viewBox="0 0 24 24" className=navbarItem>
              <path d="M10 20v-6h4v6h5v-8h3L12 3 2 12h3v8z" />
              <path d="M0 0h24v24H0z" fill="none" />
            </svg>
          </Link>
        </li>
        <li className=appNavItem>
          <Link href="/current-energy-price">
            <svg
              width="50" height="50" viewBox="0 0 24 24" className=navbarItem>
              <path
                d="M11.99 2C6.47 2 2 6.48 2 12s4.47 10 9.99 10C17.52 22 22 17.52 22 12S17.52 2 11.99 2zM12 20c-4.42 0-8-3.58-8-8s3.58-8 8-8 8 3.58 8 8-3.58 8-8 8z"
              />
              <path d="M0 0h24v24H0z" fill="none" />
              <path d="M12.5 7H11v6l5.25 3.15.75-1.23-4.5-2.67z" />
            </svg>
          </Link>
        </li>
        <li className=appNavItem>
          <Link href="/settings">
            <svg
              width="50" height="50" viewBox="0 0 20 20" className=navbarItem>
              <path fill="none" d="M0 0h20v20H0V0z" />
              <path
                d="M15.95 10.78c.03-.25.05-.51.05-.78s-.02-.53-.06-.78l1.69-1.32c.15-.12.19-.34.1-.51l-1.6-2.77c-.1-.18-.31-.24-.49-.18l-1.99.8c-.42-.32-.86-.58-1.35-.78L12 2.34c-.03-.2-.2-.34-.4-.34H8.4c-.2 0-.36.14-.39.34l-.3 2.12c-.49.2-.94.47-1.35.78l-1.99-.8c-.18-.07-.39 0-.49.18l-1.6 2.77c-.1.18-.06.39.1.51l1.69 1.32c-.04.25-.07.52-.07.78s.02.53.06.78L2.37 12.1c-.15.12-.19.34-.1.51l1.6 2.77c.1.18.31.24.49.18l1.99-.8c.42.32.86.58 1.35.78l.3 2.12c.04.2.2.34.4.34h3.2c.2 0 .37-.14.39-.34l.3-2.12c.49-.2.94-.47 1.35-.78l1.99.8c.18.07.39 0 .49-.18l1.6-2.77c.1-.18.06-.39-.1-.51l-1.67-1.32zM10 13c-1.65 0-3-1.35-3-3s1.35-3 3-3 3 1.35 3 3-1.35 3-3 3z"
              />
            </svg>
          </Link>
        </li>
      </ul>
    </nav>,
};