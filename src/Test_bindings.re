open Ctypes;
module M = (F: FOREIGN) => {
  open F;
  let sum = foreign("sum", int @-> int @-> returning(int));
};
