macCLI
======

Utility tool for CloudBuilder.

## CLI and automatic testing

### Basics


CLI can run script files bu suing the command `script filename`
The directory where the filename is searched, is the default one atthe launch of the application (OS dependant), and can be changed with the command `cd path` as in a shell.

### List of commands
The simplest script is a collection on lines conainting a sinble command accepted by the CLI on interactive mode.

By example, 

	setup
	loginanonymous
	
This wil give the following results


	> setup
	>>  : {
		"_error":	0
	}
	Done. (in 4 ms.)
	> loginanonymous
	>>  : {
		"result":	{
			"network":	"anonymous",
			"networkid":	"54125f1b27ef731d269b5781",
			"registerTime":	"2014-09-12T02:48:59.414Z",
			"registerBy":	"cloudbuilder",
			"games":	[{
					"appid":	"cloudbuilder",
					"ts":	"2014-09-12T02:48:59.414Z"
				}],
			"profile":	{
				"displayName":	"Guest",
				"lang":	"en"
			},
			"_id":	"54125f1b27ef731d269b5782",
			"gamer_id":	"54125f1b27ef731d269b5782",
			"gamer_secret":	"25fb1070f915f74cd41b61a1fd976bf4437b7cbc"
		},
		"_httpcode":	200
	}
	Done. (in 635 ms.)

In this case, commond are simply executed, and no control are made on their results.


### Check a result
To activate controls, the immediate line after each command to check, must start by the character `#` followed by a `json`

	setup
	# { "$._error" = 0 }

In this case, the result of the command is verified to determine if it maches with the expected result passed in the json contained in this line.

See [Expected Result](#expected) to get a description of the json to pass

When excuted, 2 cases could arrive:

- passed : the result is conform to the expected one, success!
- missed : the result do no match the expected one, failure!

At the end of the script, CLI will gives a summary of the missed commands, and then an overall summary in the form of

	--- Tests summary ---

   	3 Tests
   	1 Passing
   	2 Missing
	
	---


### Flow control
It is possible to tell that part of a script to should be `skipped` or `preferred` (means played exclusively)

In this case, the first character following the `#` could be either `+`or `-`
where:

	- : the command is skipped
	+ : all the others command, which are not themself defined by #+, are skipped. 
	
**Note**: the `#+` modifier is only active if in the precedents lines of the script the options `@only` has been found, whitout this option, the command is executed in a standard way (see [Options](#options))


### [Expected result](id:expected)
For each test, the result returned by the command (`CCloudResult`) is evaluate against the expected json.
the `CCloudResult` is a json containing a control fields (_httpcode, _error, ...) and usually a "result" field, as returned by the server.

	{
		"result":	{
			"network":	"anonymous",
			"networkid":	"54125f1b27ef731d269b5781",
			"registerTime":	"2014-09-12T02:48:59.414Z",
			"registerBy":	"cloudbuilder",
			"games":	[{
					"appid":	"cloudbuilder",
					"ts":	"2014-09-12T02:48:59.414Z"
				}],
			"profile":	{
				"displayName":	"Guest",
				"lang":	"en"
			},
			"_id":	"54125f1b27ef731d269b5782",
			"gamer_id":	"54125f1b27ef731d269b5782",
			"gamer_secret":	"25fb1070f915f74cd41b61a1fd976bf4437b7cbc"
		},
		"_httpcode":	200
	}

To evaluate a control field, the expected json must specify the field name preceding by the `$` sign : 

	"$._httpcode" : 200
	
	This will verify that the returned _httpcode is equal to 200

To evaluate a result field, just add it to the expected json. To specify a field of an ambedded json, use the `.` as delimeter.

	"network" : "anonymous"
	"profile.lang" : "en"

	the result must contains a field network equal to "anonymous"" AND a json profile, itself containing the field lang equal to "en"

### [Operators](id:operators)

The following operators can be used to evaluate the result.

operator | sample | description | options
--------| -------- | --------- | ------
  | "$._httpcode" : 200 | _httpcode must be equal to 200
`in` | "code" : {"in" : [0,1] } | code must be either 0 or 1
`gt` | "count" : {"gt" : 1 } | count must be greather than 1
`lt` | "count" : {"lt" : 100 } | count must be lower than 100
`is` | "count" : {"is" : "number"} | count must be a number |  "number", "string", "array"
`exist` | "gamer_id" : {"exist" : true} | the result must contain a field gamer_id |  "true , "false"
`contains` | "games" : {"contains" : {"appid" : "cloudbuilder"}} | the array games must contain an item where the field appid is equal to cloudbuilder 
`notContains` | "games" : {"contains" : {"appid" : "cloudbuilder"}} | the array games must NOT contain an item where the field appid is equal to cloudbuilder
`empty` | "gamer_id" : {"empty" : true} | the result must be an empty array or object with no attributes |  "true , "false"


*`contains` and `notContains` apply only `array` fields and the value type must be a `number` or a `string` exclusively.*

#####sample :

	loginanonymous
	# {"$._httpcode" : 200,  "games" : {"contains" : {"appid" : "cloudbuilder"}}, "profile.displayName" : "Guest", "registerTime" : {"gt" : "2010-09-12T02:48:59.414Z" } }


### [Options](id:options)

To specify an option, the line must start by the `@` symbol. 

The flow control options supported are:

- `@only` : in the rest of the script, only the line preceded by `#+` will be runned.
- `@all` : run all the rest of the script by ommiting the `#+`and `#-` options.
- `@ a_json`: add the `a_json` to the parameters to be used in the following lines of the script. is the is multiple line @ json, parameters are concatened.


### Variables

Variable can be used in a script, in command and/or expected result. Just specify it by using the character `&` where the value must be remplaced. the var must be defined before is used via the option  `@ json`

	@ { "userid" : "54125f1b2d269b5782", "token" : "25fb1070f9976bf4437b7cbc"}
		
	login &userid &token
	# {"$._httpcode" : 200 , "gamer_id" : "&userid" }

As an additional helpers, when the `setup` method is called, its automatically load a file named `context-{game-alias}-{env-alias}.json` in the scripts folder if its exists.

the demo one is named context-demo-sandbox.json and contains:

    {
    "batman" : "5413104110027de8301d6ba4",
    "batmansecret" : "7edddda308f88dfd24238e6f72c3e793140c4a11",
    "ironman": "54130ff610027de8301d6ba2",
    "ironmansecret": "4f4c2a459c224e3c73ebe9ab36687496fd82f527",
    "wonderwoman": "5413105710027de8301d6ba6",
    "wonderwomansecret": "54636c34ea8a851694a8fcd5bfc30bdce1e9786b"
    }

### Others

Comments are delimited by -- (currently only to be in the beginning of a new line). The line is then ignored.
