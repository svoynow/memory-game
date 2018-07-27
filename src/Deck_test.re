open Jest;
open Deck;
open Expect;

let findCard = (deck, card) =>
  Card.(
    List.find(c => c.animal == card.animal && c.group == card.group, deck)
  );

describe("makeDeck", () =>
  test("number of cards is twice the number of pairs requested", _ =>
    expect(makeDeck(8) |> List.length) |> toEqual(16)
  )
);

describe("flip card", () => {
  let deck = makeDeck(8);

  test("flips face down card face up", _ => {
    let card = List.nth(deck, 6);
    let flipped = flipCard(deck, card);
    expect(findCard(flipped, card).state) |> not_ |> toEqual(card.state);
  });

  test("it doesn't matter if you do it more than once", _ => {
    let card = List.nth(deck, 6);
    let flipped = flipCard(flipCard(flipCard(deck, card), card), card);
    expect(findCard(flipped, card).state) |> not_ |> toEqual(card.state);
  });
});

describe("reset card", () => {
  let deck = makeDeck(8);

  test("flips face up card face down", _ => {
    let card = List.nth(deck, 6);
    let reset = resetCard(flipCard(deck, card), card);
    expect(findCard(reset, card).state) |> toEqual(card.state);
  });

  test("it doesn't matter if you do it more than once", _ => {
    let card = List.nth(deck, 6);
    let reset =
      resetCard(
        resetCard(resetCard(flipCard(deck, card), card), card),
        card,
      );
    expect(findCard(reset, card).state) |> toEqual(card.state);
  });
});