open Jest;
open Card;
open Expect;

let [x, y, ..._tl] = makePair(Animal.Chicken);
let [x2, y2, ..._tl] = makePair(Animal.Whale);

describe("makePair", () => {
  test("pairs have the same value", _ =>
    expect(x.animal) |> toEqual(y.animal)
  );

  test("pairs have different groups", _ =>
    expect(x.group) |> not_ |> toEqual(y.group)
  );
});

describe("key", () => {
  test("pairs have different keys", _ =>
    expect(key(x)) |> not_ |> toEqual(key(y))
  );
  test("different animals produce different keys", _ =>
    expect(key(x2)) |> not_ |> toEqual(key(x))
  );
});

describe("isMatch", () => {
  test("pairs match", _ =>
    expect(isMatch(x, y)) |> toBe(true)
  );
  test("cards with different animals don't match", _ =>
    expect(isMatch(x2, y)) |> toBe(false)
  );
});