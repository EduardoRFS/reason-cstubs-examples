let prefix = "test";

let prologue = "#include \"test.h\"";

let () = {
  let (generate_ml, generate_c) = (ref(false), ref(false));
  let () =
    Arg.(
      parse([
        ("-ml", Set(generate_ml), "Generate ML"),
        ("-c", Set(generate_c), "Generate C"),
      ])
    )(
      _ => failwith("unexpected anonymous argument"),
      "stubgen [-ml|-c]",
    );

  switch (generate_ml^, generate_c^) {
  | (false, false)
  | (true, true) => failwith("Exactly one of -ml and -c must be specified")
  | (true, false) =>
    Cstubs.write_ml(Format.std_formatter, ~prefix, (module Test_bindings.M))
  | (false, true) =>
    print_endline(prologue);
    Cstubs.write_c(Format.std_formatter, ~prefix, (module Test_bindings.M));
  };
};
