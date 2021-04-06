(* https://codeforces.com/contest/1484/submission/110668531 *)
let infinite_c = 1_000_000 (* "infinite" capacity *)

let maxflow s t adj cap =
  (* s and t are nodes (numbers). g is a graph (represented via an
     array of adjacency lists). c is a 1-d array of capacities.  The
     adjacency list on node v stores pairs like (w,i) where w is the
     other node, and i is the index into the capacity array for where
     this capacity is stored.  It's set up so that i lxor 1 is where the
     capacity of edge (w,v) is stored.  We compute the maximum flow in
     the same representation as the capacities.  It returns (f,resid)
     where f is the maximum flow, and resid is the residual capacities
     that result from that flow.
  *)

  let c = Array.copy cap in
  let n = Array.length adj in
  let alive = Array.make n [] in
  let level = Array.make n 0 in
  let queue = Array.make n 0 in
  let front = ref 0 in
  let back = ref 0 in

  let push w = queue.(!back) <- w; back := !back+1 in
  let eject() = let x = queue.(!front) in front := !front + 1; x; in

  let rec bfs () = 
    let rec loop () = 
      if !front = !back then false else
	let v = eject() in
	if level.(v) = level.(t) then true else (
	  List.iter ( 
	    fun (w,i) -> if level.(w) < 0 && c.(i) > 0 then (
	      level.(w) <- level.(v) + 1;
	      push w
	    )
	  ) adj.(v);
	  loop ()
	)
    in
    level.(s) <- 0;
    back := 0; front := 0;
    push s;
    loop ();
  in
    
  let rec dfs v cap = 
    (* Does a DFS from v looking for a path to t.  It tries to push cap units
       of flow to t.  It returns the amount of flow actually pushed *)
    if v=t then cap else
      let rec loop total remaining li = 
	match li with 
	  | [] -> 
	    alive.(v) <- [];
	    total
	  | (w,i)::tail -> 
	    if level.(w) = level.(v)+1 && c.(i) > 0 then (
	      let p = dfs w (min c.(i) remaining) in
	      c.(i) <- c.(i) - p;
	      c.(i lxor 1) <- c.(i lxor 1) + p;
	      if remaining-p = 0 then (
		alive.(v) <- li;
		total+p
	      ) else loop (total+p) (remaining-p) tail
	    ) else loop total remaining tail
      in loop 0 cap alive.(v)
  in
  
  let rec main_loop flow_so_far = 
    Array.fill level 0 n (-1);
    Array.blit adj 0 alive 0 n;
    if bfs () then main_loop (flow_so_far + (dfs s infinite_c)) else (flow_so_far, c)
  in
  main_loop 0

(* end flow *)

let rec fold i j f init = if i>j then init else fold (i+1) j f (f i init)
let sum i j f = fold i j (fun i a -> (f i) + a) 0

open Printf
open Scanf
  
let read_int _ = bscanf Scanning.stdib " %d " (fun x -> x)
let read_pair _ = bscanf Scanning.stdin " %d %d " (fun x y -> (x,y))  

let () =
  let cases = read_int() in
  for case = 1 to cases do

    let (n,m) = read_pair () in

    let nn = n + m + 2 in
    
    let graph = Array.make nn [] in

    let index = ref 0 in
    let add_edge u v =
      let i = !index in
      graph.(u) <- (v,i)::graph.(u);
      graph.(v) <- (u,i+1)::graph.(v);
      index := i+2
    in

    let (s,t) = (nn-2, nn-1) in

    for day=0 to m-1 do
      let k = read_int() in
      for j = 0 to k-1 do
	let f = -1 + read_int() in
	add_edge day (m+f)
      done;
    done;
    
    for day=0 to m-1 do
      add_edge s day;
    done;

    for friend=m to n+m-1 do
      add_edge friend t;
    done;

    let mm = !index in

    let cap = Array.init mm (fun i -> (i+1) land 1) in

    for friend = m to n+m-1 do
      List.iter (fun (v,i) -> if v = t then cap.(i) <- (m+1)/2) graph.(friend)
    done;
    let (f,final_cap) = maxflow s t graph cap in
    if f < m then printf "NO\n" else (
      printf "YES\n";
      for day = 0 to m-1 do
	List.iter (fun (v,j) ->
	  if v <> s && final_cap.(j) = 0 then 
	    printf "%d " (v-m+1)) graph.(day)
      done;
      print_newline()
    )
  done
