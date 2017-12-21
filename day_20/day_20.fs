open System
//module <%= namespace %>

// needed to make inference work e.g. num.MaxValue ???
// cite here: 
type num = int32

// let turning (vx,vy,vz) (ax,ay,az) =
//     (ax<>0 && vx*ax<=0) || (ay<>0 && vy*ay<=0) || (az<>0 && vz*az<=0)

// let closest particle = 
//     let rec closest particle best prev =
//         let ((x,y,z),vel,acc) = particle
//         let dist = abs x + abs y + abs z
//         let turning = turning vel acc
//         if dist > best && dist > prev && not turning
//             then best
//             else closest (simulate particle) (min dist best) dist
//     closest particle num.MaxValue num.MaxValue

// simulate ((3,0,0),(2,0,0),(-1,0,0))
// simulate ((5,0,0),(1,0,0),(-1,0,0))
// simulate ((6,0,0),(0,0,0),(-1,0,0))
// simulate ((6,0,0),(0,0,0),(-1,0,0))
// simulate ((6,0,0),(-1,0,0),(-1,0,0))
// simulate ((5,0,0),(-2,0,0),(-1,0,0))

// closest ((195,876,2298),(-67,35,-60),(6,-9,-7))
// closest ((-43,1145,952),(14,-92,-96),(-2,-5,0))

// closest ((3,0,0),(2,0,0),(-1,0,0))
// (min 9 7)



//let test= "p=<-2690,232,17>, v=<-377,29,2>, a=<25,1,0>"

//test.Split ' '


//let bestdistance = fun (particle,best) p b -> if best<b then (particle,best) else (p,b)
//bestdistance (6,4) 5 6


// read lines
// split lines and get 9 - tuple
// number particles
// simulate particles until none remain
    // compute distance from origin
    // compute new position and save for particle
    // if further away, eliminate particle, and update best distance

// iterate and print lines
// lines "day_20.ts1" 
//     |> Seq.map to9tuple
//     |> Seq.indexed
//     |> Seq.map (fun (p,particle) -> (p, closest particle))
//     |> Seq.toList
// //    |> List.map (fun (p,c) -> printfn "particle: %i closest: %i " p c)
//     |> List.minBy (fun (p,c) -> abs c)
    
// -> (315,15)





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
lines "day_20\\day_20.ts2" 
    |> Seq.map to9tuple
    |> Seq.indexed
    |> Seq.sortBy(fun (n,((x,y,z),_,_)) -> abs x + abs y + abs z)
    |> Seq.sortBy(fun (n,(_,(vx,vy,vz),_)) -> abs vx + abs vy + abs vz)
    |> Seq.sortBy(fun (n,(_,_,(ax,ay,az))) -> abs ax + abs ay + abs az)
    |> Seq.toList

// let rec runUntilStableHelper state count =
//     let mutable steps = count
//     let mutable state = state
//     while steps > 0 do
// //        state <- Seq.distinctBy (fun (pos,_,_)->pos) state
//         state <- Seq.map simulate state
//         steps <- steps+(-1)
//     state

// let runUntilStable state =
//     let rec loop = function
//         | (0,state) -> state
//         | (count,state) -> loop (count+(-1),Seq.map simulate state)
//     loop (10000,state)

// Part 2
// simulate until no particles:
// - are turning
// - are getting closer
// lines "day_20.ts3" 
//     |> Seq.map to9tuple
//     |> runUntilStable 
//     |> Seq.toList
//     |> Seq.length
//     |> (fun x -> printfn "%i" x)

let simulate particle =
    let ((x,y,z),(vx,vy,vz),(ax,ay,az)) = particle
    ((x+vx,y+vy,z+vz),(vx+ax,vy+ay,vz+az),(ax,ay,az))


let dist ((x,y,z),_,_) = abs x + abs y + abs z

let stepAll state =     // group by position, and filter by non-colliding
    state 
    |> Seq.groupBy (fun (pos,_,_)->pos)
    |> Seq.filter (fun (_,state) -> Seq.length state =1)
    |> Seq.collect (fun (_,p) -> p)
    |> Seq.map simulate

let particleCount state =
    let next = stepAll state
    Some (Seq.length next,next)

let state = 
    lines "day_20\\day_20.ts2" 
    |> Seq.map to9tuple

// state 
// |> Seq.map simulate
// |> Seq.groupBy (fun (pos,_,_)->pos)
// |> Seq.toList

// |> Seq.groupBy (fun (pos,_,_)->pos)
// |> Seq.map (fun (pos,sq)->(pos,Seq.length sq))
// |> Seq.toList

for v in Seq.unfold particleCount state do
    printfn "%A" v
