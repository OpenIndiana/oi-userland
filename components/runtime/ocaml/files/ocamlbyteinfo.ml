(***********************************************************************)
(*                                                                     *)
(*                           Objective Caml                            *)
(*                                                                     *)
(*            Xavier Leroy, projet Gallium, INRIA Rocquencourt         *)
(*                                                                     *)
(*  Copyright 2009 Institut National de Recherche en Informatique et   *)
(*  en Automatique.  All rights reserved.  This file is distributed    *)
(*  under the terms of the GNU Library General Public License, with    *)
(*  the special exception on linking described in file ../../LICENSE.  *)
(*                                                                     *)
(***********************************************************************)

(* $Id: ocamlbyteinfo.ml,v 1.1 2010/01/11 18:45:03 rjones Exp $ *)

(* Dumps a bytecode binary file *)

open Sys
open Dynlinkaux

let input_stringlist ic len =
  let get_string_list sect len =
    let rec fold s e acc =
      if e != len then
        if sect.[e] = '\000' then
          fold (e+1) (e+1) (String.sub sect s (e-s) :: acc)
        else fold s (e+1) acc
      else acc
    in fold 0 0 []
  in
  let sect = String.create len in
  let _ = really_input ic sect 0 len in
  get_string_list sect len

let print = Printf.printf
let perr s =
  Printf.eprintf "%s\n" s;
  exit(1)
let p_title title = print "%s:\n" title

let p_section title format pdata = function
  | [] -> ()
  | l ->
      p_title title;
      List.iter
        (fun (name, data) -> print format (pdata data) name)
        l

let p_list title format = function
  | [] -> ()
  | l ->
      p_title title;
      List.iter
        (fun name -> print format name)
        l

let _ =
  try
    let input_name = Sys.argv.(1) in
    let ic = open_in_bin input_name in
    Bytesections.read_toc ic;
    List.iter
      (fun section ->
         try
           let len = Bytesections.seek_section ic section in
           if len > 0 then match section with
             | "CRCS" ->
                 p_section
                   "Imported Units"
                   "\t%s\t%s\n"
                   Digest.to_hex
                   (input_value ic : (string * Digest.t) list)
             | "DLLS" ->
                 p_list
                   "Used Dlls" "\t%s\n"
                   (input_stringlist ic len)
             | "DLPT" ->
                 p_list
                   "Additional Dll paths"
                   "\t%s\n"
                   (input_stringlist ic len)
             | "PRIM" ->
                 let prims = (input_stringlist ic len) in
                 print "Uses unsafe features: ";
                 begin match prims with
                     [] -> print "no\n"
                   | l  -> print "YES\n";
                       p_list "Primitives declared in this module"
                         "\t%s\n"
                         l
                 end
             | _ -> ()
         with Not_found | Failure _ | Invalid_argument _ -> ()
      )
      ["CRCS"; "DLLS"; "DLPT"; "PRIM"];
    close_in ic
  with
    | Sys_error msg ->
        perr msg
    | Invalid_argument("index out of bounds") ->
        perr (Printf.sprintf "Usage: %s filename" Sys.argv.(0))
