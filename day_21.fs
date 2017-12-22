#light



let r = [|
    ("...#","##.#.....");
    (".#...####","#..#........#..#");
|]

let isqrt x =
    let rec isqrt r x = 
        if r * r >= x then r else isqrt (r+1) x
    isqrt 1 x
    
let input = ".#...####"     // 9
let input = ".#...####"     // 9

let split2 strlen =     // provide character indexes
    let side = isqrt strlen
    if side % 2 <> 0 then [] else
        [for r in 0..side/2-1 do
            for c in 0..side/2-1 do
                let r = r*2*side
                yield [r+c*2;r+c*2+1;r+c*2+side;r+c*2+side+1]]
let split3 strlen =     // provide character indexes
    let side = isqrt strlen
    if side % 3 <> 0 then [] else
        [for r in 0..side/3-1 do
            for c in 0..side/3-1 do
                let r = r*3*side
                yield [r+c*3;r+c*3+1;r+c*3+2;
                       r+c*3+side;r+c*3+side+1;r+c*3+side+2;
                       r+c*3+2*side;r+c*3+2*side+1;r+c*3+2*side+2]]

//split3 36

let findMatch rules input =
    let indexes = split3 (String.length input)
    indexes

findMatch ["....";"....";] input
