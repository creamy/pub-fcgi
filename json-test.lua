#!/usr/local/bin/lua

-- dem.fetch json result from http://fcgi.creamy.mobi/pub/json
-- parse and dump results
-- ex: http://lua.creamy.mobi/json-test.lua
-- Waitman Gobble
-- waitman@waitman.net
-- +1.6503967580

local http = require("socket.http")
local ltn12 = require("ltn12")
local json = require("json")

print "Content-Type: text/html"
print ""
print ""

local t = {}
http.request{
	url = "http://fcgi.creamy.mobi/pub/json",
	sink = ltn12.sink.table(t)
}
local res = json.decode(table.concat(t))
table.foreach(res,print)
