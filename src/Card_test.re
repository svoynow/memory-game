open Jest;
open Card;
open Expect;

let [x, y, ..._tl] = makePair(Animal.Chicken);
let [x2, y2, ..._tl] = makePair(Animal.Whale);

describe("makePair", () => {
  test("pairs have the same value", _ =>
    expect(x.animal) |> toEqual(y.animal)
  );

  test("pairs have the same state", _ =>
    expect(x.state) |> toEqual(y.state)
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

describe("flip", () => {
  test("changes the state of a face down card to face up", _ =>
    expect(flip(x).state) |> not_ |> toEqual(x.state)
  );

  test("it doesn't matter if you flip more than once", _ =>
    expect(flip(flip(flip(x))).state) |> toEqual(flip(x).state)
  );
});

describe("reset", () => {
  test("changes the state of a face up card to face down", _ =>
    expect(reset(flip(x)).state) |> toEqual(x.state)
  );

  test("it doesn't matter if you reset more than once", _ =>
    expect(reset(reset(reset(flip(x)))).state) |> toEqual(x.state)
  );
});