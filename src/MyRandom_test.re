open Jest;

describe("sample", () => {
  open Expect;

  let xs = [1, 2, 3, 4, 5];

  test("returns the right number of items", _ =>
    expect(List.length(MyRandom.sample(xs, 3))) |> toBe(3)
  );
  test("returns only items in the original list", _ =>
    expect(MyRandom.sample(xs, 3) |> List.for_all(x => List.mem(x, xs)))
    |> toBe(true)
  );
});