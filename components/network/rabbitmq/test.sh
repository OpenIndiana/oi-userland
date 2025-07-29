#!/bin/bash
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2018, 2021, Oracle and/or its affiliates.
#

# Script rabbitmq-server requires GNU version of grep.
export PATH=/usr/gnu/bin:/usr/bin:/usr/sbin

if [ $# -ne 2 ]; then
  echo "Testing script requires two arguments!"
  echo "usage: $0 <RABBITMQ_SOURCE_DIR> <RABBITMQ_TEMP_DIR>"
  exit 1
fi

RABBITMQ_SOURCE_DIR="$1"
RABBITMQ_TEMP_DIR="$2"
mkdir -p "${RABBITMQ_TEMP_DIR}" 2> /dev/null

if [ ! -d "${RABBITMQ_SOURCE_DIR}" -o ! -d "${RABBITMQ_TEMP_DIR}" ]; then
  echo "Invalid input arguments! They should be directories!" >&2
  exit 1
fi

if [ ! -w "${RABBITMQ_TEMP_DIR}" ]; then
  echo "Temp directory is not writeable!" >&2
  exit 1
fi


########################### START RABBITMQ SERVER ###########################

# We use RabbitMQ bash scripts from the current build tree.
RABBITMQ_SERVER_BIN="${RABBITMQ_SOURCE_DIR}/sbin/rabbitmq-server"
RABBITMQ_CTL_BIN="${RABBITMQ_SOURCE_DIR}/sbin/rabbitmqctl"
RABBITMQ_PLUGINS_BIN="${RABBITMQ_SOURCE_DIR}/sbin/rabbitmq-plugins"

# Path to RabbitMQ plugins.
export RABBITMQ_PLUGINS_DIR="${RABBITMQ_SOURCE_DIR}/plugins"

# Setup paths to RabbitMQ temporary directories.
export RABBITMQ_PID_FILE="${RABBITMQ_TEMP_DIR}/rabbit.pid"
export RABBITMQ_LOG_BASE="${RABBITMQ_TEMP_DIR}/rabbit/log"
export RABBITMQ_MNESIA_BASE="${RABBITMQ_TEMP_DIR}/mnesia"
export RABBITMQ_MNESIA_DIR="${RABBITMQ_TEMP_DIR}/mnesia/rabbit"
export RABBITMQ_SCHEMA_DIR="${RABBITMQ_TEMP_DIR}/schema"
export RABBITMQ_GENERATED_CONFIG_DIR="${RABBITMQ_TEMP_DIR}/config"
export RABBITMQ_PLUGINS_EXPAND_DIR="${RABBITMQ_TEMP_DIR}/plugins"
export RABBITMQ_ENABLED_PLUGINS_FILE="${RABBITMQ_TEMP_DIR}/enabled_plugins"

# If a failure occurred in previous runs, we need to clean it up.
rm "${RABBITMQ_PID_FILE}" 2> /dev/null
PREV_RABBIT_PID=$(ps -ef | grep "beam.smp" | grep "${RABBITMQ_TEMP_DIR}" | awk '{print $2}')
if [ ! -z "${PREV_RABBIT_PID}" ]; then
  echo "killed"
  kill -9 "${PREV_RABBIT_PID}"
fi

# Initiate the execution of RabbitMQ server and wait for it.
mkdir -p "${RABBITMQ_LOG_BASE}"
${RABBITMQ_SERVER_BIN} > "${RABBITMQ_LOG_BASE}/startup_log" 2> "${RABBITMQ_LOG_BASE}/startup_err" &
${RABBITMQ_CTL_BIN} --timeout 20 wait "${RABBITMQ_PID_FILE}" 1> /dev/null
if [ $? -ne 0 ]; then
  echo "Failed to start RabbitMQ server!" >&2
  exit 2
fi

echo "RabbitMQ server successfully started."
echo ""


############################## PING-PONG TEST ##############################

# Create a new empty dir for ping-pong test.
PINGPONG_TEST_DIR="${RABBITMQ_TEMP_DIR}/pingpong_test"
rm -Rf "${PINGPONG_TEST_DIR}"
mkdir -p "${PINGPONG_TEST_DIR}"
cd "${PINGPONG_TEST_DIR}"

# Create the Erlang source code for pingpong_common module.
# The exported functions are used by client applications.
# key methods: set_code_paths, send_msg, recv_msg
cat << PINGPONG > pingpong_common.erl
-module(pingpong_common).

-import(code, [add_pathz/1]).
-export([set_code_paths/0, send_msg/5, recv_msg/4]).

-include_lib("amqp_client.hrl").

% Set code paths required to run the client application.
set_paths([]) -> ok;
set_paths([Dir|Rest]) ->
  code:add_pathz(Dir),
  code:add_pathz(Dir++"/ebin"),
  set_paths(Rest).

set_code_paths() ->
  DepPaths = [ %%%DEP_LINKS%%% ],
  set_paths(DepPaths).

% Convert list of strings to list of binaries.
convert_args([], L) -> lists:reverse(L);
convert_args([H|T], L) -> convert_args(T, [list_to_binary(H)|L]).

% Send a message to RabbitMQ server.
send_msg(RabbitHost, QueueStr, MsgStr, UserStr, PasswdStr) ->
  [Queue, Msg, User, Passwd] = convert_args([QueueStr, MsgStr, UserStr, PasswdStr], []),
  {ok, Connection} = amqp_connection:start(#amqp_params_network{
    host = RabbitHost, username = User, password = Passwd}),
  {ok, Channel} = amqp_connection:open_channel(Connection),
  amqp_channel:call(Channel, #'queue.declare'{queue = Queue}),
  amqp_channel:cast(Channel, #'basic.publish'{exchange = <<"">>,
    routing_key = Queue}, #amqp_msg{payload = Msg}),
  ok = amqp_channel:close(Channel),
  ok = amqp_connection:close(Connection), ok.

% Receive a message from RabbitMQ server.
recv_msg(RabbitHost, QueueStr, UserStr, PasswdStr) ->
  [Queue, User, Passwd] = convert_args([QueueStr, UserStr, PasswdStr], []),
  {ok, Connection} = amqp_connection:start(#amqp_params_network{
    host = RabbitHost, username = User, password = Passwd}),
  {ok, Channel} = amqp_connection:open_channel(Connection),
  amqp_channel:call(Channel, #'queue.declare'{queue = Queue}),
  amqp_channel:subscribe(Channel,
    #'basic.consume'{queue = Queue, no_ack = true}, self()),
  receive
    #'basic.consume_ok'{} -> ok
  end,
  receive
    {#'basic.deliver'{}, #amqp_msg{payload = Msg}} -> Msg
  end,
  ok = amqp_channel:close(Channel),
  ok = amqp_connection:close(Connection), Msg.
PINGPONG

# Create the Erlang source code for 'ping' client application.
cat << PING > ping.erl
-module(ping).

-import(pingpong_common, [set_code_paths/0, send_msg/5, recv_msg/4]).
-export([main/1]).

main([RabbitHost]) -> main([RabbitHost, "guest", "guest"]);
main([RabbitHost, User, Passwd]) -> set_code_paths(),
  io:format("client 1: Message '~p' sent!~n", [<<"ping">>]),
  send_msg(RabbitHost, "ping_queue", "ping", User, Passwd),
  Pong = recv_msg(RabbitHost, "pong_queue", User, Passwd),
  io:format("client 1: Received '~p' message!~n", [Pong]),
  halt(0).
PING

# Create the Erlang source code for 'pong' client application.
cat << PONG > pong.erl
-module(pong).

-import(pingpong_common, [set_code_paths/0, send_msg/5, recv_msg/4]).
-export([main/1]).

main([RabbitHost]) -> main([RabbitHost, "guest", "guest"]);
main([RabbitHost, User, Passwd]) -> set_code_paths(),
  Ping = recv_msg(RabbitHost, "ping_queue", User, Passwd),
  io:format("client 2: Received '~p' message!~n", [Ping]),
  io:format("client 2: Message '~p' sent!~n", [<<"pong">>]),
  send_msg(RabbitHost, "pong_queue", "pong", User, Passwd),
  halt(0).
PONG

# Copy and extract required plugin dependencies.
cd "${RABBITMQ_PLUGINS_DIR}/"
cp -r * "${PINGPONG_TEST_DIR}"

cd "${PINGPONG_TEST_DIR}/"
find . -name '*.ez' -exec unzip {} > /dev/null \;
rm *.ez

# Find the directories required as dependencies and create version-free links.
DEP_DIRS=($(find . -maxdepth 1 ! -path . -type d | perl -pe 's/\.\///'))

DEP_LINKS=()
for ((i = 0; i < ${#DEP_DIRS[@]}; i++))
do
  DEP_DIR="${DEP_DIRS[$i]}"
  DEP_LINK=$(echo "${DEP_DIR}" | perl -pe 's/-.*//')
  ln -s "${DEP_DIR}" "${DEP_LINK}"
  DEP_LINKS+=(\"$DEP_LINK\")
done

# Fill the list of dependency links in pingpong_common module.
perl -i -pe "s/%%%DEP_LINKS%%%/$(IFS=','; echo "${DEP_LINKS[*]}")/" pingpong_common.erl

# Compile client applications.
erlc -I amqp_client/include/ *.erl

# Test that Erlang client applications can
# send/receive messages to/from RabbitMQ server.
#
# Testing scenario (client1/ping, client2/pong):
# 1) client1 sends "ping" message to RabbitMQ server ('ping_queue')
# 2) client2 receives "ping" message" from RabbitMQ server ('ping_queue')
# 3) client2 sends "pong" message to RabbitMQ server ('pong_queue')
# 4) client1 receives "pong" message" from RabbitMQ server ('pong_queue')
echo "Ping-pong testing scenario:"
erl -noshell -run ping main localhost -s init stop &
PING_PID="$!"
erl -noshell -run pong main localhost -s init stop &
PONG_PID="$!"

wait "${PONG_PID}"
wait "${PING_PID}"


############################## RABBITMQ UTILS ##############################

echo ""
echo "Available queues on RabbitMQ server:"
${RABBITMQ_CTL_BIN} list_queues name state | grep '_queue' | sort

echo ""
${RABBITMQ_PLUGINS_BIN} enable --all 1>/dev/null
${RABBITMQ_PLUGINS_BIN} list -Em

########################### STOP RABBITMQ SERVER ###########################

${RABBITMQ_CTL_BIN} stop "${RABBITMQ_PID_FILE}" 1> /dev/null
if [ $? -ne 0 ]; then
  echo "Failed to stop RabbitMQ server!" >&2
  exit 2
fi

echo ""
echo "RabbitMQ server successfully stopped."

# Create the tarball for manual testing.
cd "${RABBITMQ_TEMP_DIR}"
gtar cjf pingpong_test.tar.bz "${PINGPONG_TEST_DIR#${RABBITMQ_TEMP_DIR}/}"

exit 0;
