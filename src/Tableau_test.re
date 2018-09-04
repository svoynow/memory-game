open Jest;
open Expect;
open Tableau;

let tableau = makeTableau(Deck.makeDeck(), ~numPairs=8);
let [a, b, ..._] as pair = makeTableau(Deck.makeDeck(), ~numPairs=1);

describe("Item", () => {
  let [item, ..._] = tableau;

  test("initialized face down", _ =>
    expect(item.cardState) |> toEqual(Item.FaceDown)
  );

  test("cards with same animal match", _ =>
    expect(Item.isMatch(a, b)) |> toBe(true)
  );

  test("cards with same animal have distinct identity", _ =>
    expect(Item.isSame(a, b)) |> toBe(false)
  );
});

describe("Tableau", () => {
  test("make tableau creates the specified number of pairs", _ =>
    expect(List.length(tableau)) |> toBe(16)
  );

  test("pairs found returns the number of pairs", _ => {
    let before = Tableau.pairsFound(tableau);
    let [a, b, ..._] = tableau;
    let after = Tableau.pairCards(tableau, [a, b]) |> Tableau.pairsFound;
    expect(after - before) |> toEqual(1);
  });

  test("flip card changes a card from face down to face up", _ => {
    let [a', b', ..._] = Tableau.flipCard(pair, a);
    expect(a'.cardState) |> toBe(Item.FaceUp);
  });

  test("flip card can be called multiple times", _ => {
    let [a', ..._] =
      pair
      |. Tableau.flipCard(a)
      |. Tableau.flipCard(a)
      |. Tableau.flipCard(a);
    expect(a'.cardState) |> toBe(Item.FaceUp);
  });

  test("reset cards sets a pair of card back to face down", _ => {
    let [a', b', ..._] =
      pair 
      |. Tableau.flipCard(a) 
      |. Tableau.resetCards([a, b])
    expect((a'.cardState, b'.cardState)) |> toEqual((Item.FaceDown, Item.FaceDown));
  });

  test("reset cards can be called multiple times", _ => {
    let [a', b', ..._] =
      pair 
      |. Tableau.flipCard(a) 
      |. Tableau.resetCards([a, b])
      |. Tableau.resetCards([a, b])
      |. Tableau.resetCards([a, b])
    expect((a'.cardState, b'.cardState)) |> toEqual((Item.FaceDown, Item.FaceDown));
  });
});