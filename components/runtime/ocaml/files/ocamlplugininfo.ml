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

(* $Id: ocamlplugininfo.ml,v 1.1 2010/01/11 18:45:03 rjones Exp $ *)

(* Dumps a .cmxs file *)

open Natdynlink
open Format

let file =
  try
    Sys.argv.(1)
  with _ -> begin
    Printf.eprintf "Usage: %s file.cmxs\n" Sys.argv.(0);
    exit(1)
  end

exception Abnormal_exit

let error s e =
  let eprint = Printf.eprintf in
  let print_exc s = function
    | End_of_file ->
       eprint "%s: %s\n" s file
    | Abnormal_exit ->
        eprint "%s\n" s
    | e -> eprint "%s\n" (Printexc.to_string e)
  in
    print_exc s e;
    exit(1)

let read_in command =
  let cmd = Printf.sprintf command file in
  let ic = Unix.open_process_in cmd in
  try
    let line = input_line ic in
    begin match (Unix.close_process_in ic) with
      | Unix.WEXITED 0 -> Str.split (Str.regexp "[ ]+") line
      | Unix.WEXITED _  | Unix.WSIGNALED _ | Unix.WSTOPPED _ ->
          error
            (Printf.sprintf
               "Command \"%s\" exited abnormally"
               cmd
            )
            Abnormal_exit
    end
  with e -> error "File is empty" e

let get_offset adr_off adr_sec =
  try
    let adr = List.nth adr_off 4 in
    let off = List.nth adr_off 5 in
    let sec = List.hd adr_sec in

    let (!) x = Int64.of_string ("0x" ^ x) in
    let (+) = Int64.add in
    let (-) = Int64.sub in

      Int64.to_int (!off + !sec - !adr)

  with Failure _ | Invalid_argument _ ->
    error
      "Command output doesn't have the expected format"
      Abnormal_exit

let print_infos name crc defines cmi cmx =
  let print_name_crc (name, crc) =
    printf "@ %s (%s)" name (Digest.to_hex crc)
  in
  let pr_imports ppf imps = List.iter print_name_crc imps in
  printf "Name: %s@." name;
  printf "CRC of implementation: %s@." (Digest.to_hex crc);
  printf "@[<hov 2>Globals defined:";
  List.iter (fun s -> printf "@ %s" s) defines;
  printf "@]@.";
  printf "@[<v 2>Interfaces imported:%a@]@." pr_imports cmi;
  printf "@[<v 2>Implementations imported:%a@]@." pr_imports cmx

let _ =
  let adr_off = read_in "objdump -h %s | grep ' .data '" in
  let adr_sec = read_in "objdump -T %s | grep ' caml_plugin_header$'" in

  let ic = open_in file in
  let _ = seek_in ic (get_offset adr_off adr_sec) in
  let header  = (input_value ic : Natdynlink.dynheader) in
    if header.magic <> Natdynlink.dyn_magic_number then
      raise(Error(Natdynlink.Not_a_bytecode_file file))
    else begin
      List.iter
        (fun ui ->
           print_infos
             ui.name
             ui.crc
             ui.defines
             ui.imports_cmi
             ui.imports_cmx)
        header.units
    end
