let sample = (list, n) => {
  let rec extract = (acc, n) =>
    fun
    | [] => raise(Not_found)
    | [h, ...t] =>
      if (n == 0) {
        (h, acc @ t);
      } else {
        extract([h, ...acc], n - 1, t);
      };
  let extract_rand = (list, len) => extract([], Random.int(len), list);
  let rec collect = (n, acc, list, len) =>
    if (n == 0) {
      acc;
    } else {
      let (picked, rest) = extract_rand(list, len);
      collect(n - 1, [picked, ...acc], rest, len - 1);
    };
  let len = List.length(list);
  collect(min(n, len), [], list, len);
};