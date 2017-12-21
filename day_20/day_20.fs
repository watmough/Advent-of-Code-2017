open System
//module <%= namespace %>

// read from file
let lines filePath = System.IO.File.ReadLines(filePath);;

let to9tuple (s : string) = 
    let s = s.Replace("<","")
    let s = s.Replace(">","")
    let s = s.Replace("p=","")
    let s = s.Replace(" v=","")
    let s = s.Replace(" a=","")
    let s = s.Replace(","," ")
    let t = s.Split  ' ' 
    let t = Array.map int64 t
    ((t.[0],t.[1],t.[2]),(t.[3],t.[4],t.[5]),(t.[6],t.[7],t.[8]))

// Part 1 - What Particle Hangs Around the Origin the Longest
// order by acceleration, velocity, position [gives correct answer - slowest accelerating one]
let part1 =
    lines "day_20\\day_20.ts2" 
        |> Seq.map to9tuple
        |> Seq.indexed
        |> Seq.sortBy(fun (n,((x,y,z),_,_)) -> abs x + abs y + abs z)
        |> Seq.sortBy(fun (n,(_,(vx,vy,vz),_)) -> abs vx + abs vy + abs vz)
        |> Seq.sortBy(fun (n,(_,_,(ax,ay,az))) -> abs ax + abs ay + abs az)
        |> Seq.toList
    lines

let simulate particle =
    let ((x,y,z),(vx,vy,vz),(ax,ay,az)) = particle
    ((x+vx,y+vy,z+vz),(vx+ax,vy+ay,vz+az),(ax,ay,az))

let stepAll state =     // group by position, and filter by non-colliding
    state 
    |> Seq.groupBy (fun (pos,_,_)->pos)
    |> Seq.filter (fun (_,state) -> Seq.length state =1)
    |> Seq.collect (fun (_,p) -> p)
    |> Seq.map simulate

let particleCount state =
    let next = stepAll2 state
    Some (Seq.length next,next)

let state = 
    lines "day_20\\day_20.ts2" 
    |> Seq.map to9tuple

// I want this to run the simulation until particles collide
// but it just stays at 1000 ... ?!??!
for v in Seq.unfold particleCount state do
    printfn "%A" v
