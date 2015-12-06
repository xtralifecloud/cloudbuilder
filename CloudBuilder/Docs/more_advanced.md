More advanced topics {#more_advanced}
===========

Using CHJSON
===========

In the CloudBuilder SDK, most of the API calls are configurable through a JSON entity called `CHJSON`, which behaves as a dictionary like a JSON object. Here is an example:

~~~~{.cpp}

CotCHelpers::CHJSON json;
json.Put("key", "value");

CotCHelpers::CHJSON subObject;
subObject.Put("hasValue", true);
json.Put("object", subObject);

cstring result = json.print(); // Results in {"key": "value", "object": {"hasValue": true}}
~~~~

To write your CHJSON objects, the following methods are recommended:

`void CotCHelpers::CHJSON::Clear()`<br/>
`void CotCHelpers::CHJSON::Delete(const char *aItem)`<br/>
`CHJSON* CotCHelpers::CHJSON::Duplicate() const`<br/>
`const CHJSON* CotCHelpers::CHJSON::Empty()`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, bool aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, int aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, double aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, const char *aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, CHJSON *aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, const CHJSON *aValue)`<br/>
`void CotCHelpers::CHJSON::Put(const char *aKey, const CHJSON& aValue)`<br/>
`CHJSON* CotCHelpers::CHJSON::parse(const char *aJsonString)`<br/>
`cstring CotCHelpers::CHJSON::print() const`<br/>
`cstring CotCHelpers::CHJSON::printFormatted() const;`

If performance is less a concern to you or if you want to do quick prototyping, you may as well use `CHJSON` objects by reference. In that case, do not forget to delete the object when not needed anymore. Note that when putting an non-const `CHJSON` object inside another however, ownership is transferred to the new container, so you do not need to delete it yourself. This enables constructs as shown below.

~~~~{.cpp}

using namespace CotCHelpers;
CHJSON *otherJson = new CHJSON;
otherJson->Put("key", "value");

CHJSON *json = new CHJSON;
json->Put("subObject", otherJson);		// ownership taken, no need to delete otherJson
// -- do not access otherJson from now, it has been rebased to json.subObject --

// Same here, the temporary object created by Parse is owned by json
json->Put("otherObj", CHJSON::parse("{\"count\": 1}"));

const CHJSON *value = json->Get("subObject");
json->Put("copy", value);		// copied, because the JSON is const

// Produces {"subObject":{"key":"value"},"otherObj":{"count":1},"copy":{"key":"value"}}
delete json;

~~~~

# Printing JSON {#pretty_print_json}

Since version 3.00, (pretty-)printing JSONs use the CotCHelpers::cstring API, which encapsulates an immutable string. Note that copying a cstring also copies the associated string, so the performance is worse than using raw char* pointers. If you need more performance, you can use the cstring& print(cstring& dest) counterpart, which directly modifies the cstring object to contain the string made from printing the JSON object and release it at the end. Assigning a value to a cstring is done via the `<<=` operator and involves no copy, just taking ownership of the string.

~~~~{.cpp}
{
	char* freeableString = strdup("hello world");
	cstring mystring;
	mystring <<= freeableString; // or cstring mystring(freeableString, true);
}
// freeableString is now freed as a result of mystring becoming out of scope.

cstring myfunc() {
	return "object"; // Creates a cstring object, copies the litteral and keeps a pointer
}
// Copies the string again in result, frees the pointer that was created in the function
cstring result = myfunc();
~~~~

Arrays
------

Arrays should not be needed, but you can create them like this:

~~~~{.cpp}

using namespace CotCHelpers;
CHJSON *array = CHJSON::Array();
CHJSON *objEntry = new CHJSON;
CHJSON *numericEntry = new CHJSON(12.0);
objEntry->Put("key", "value");
array->Add(objEntry);
array->Add(numericEntry);
// Produces [{"key": "value"}, 12]
delete array;

~~~~

Reading from CHJSON
---------

`CHJSON` objects are also used when returning a value from the SDK. Most of the calls take a callback (CloudBuilder::CResultHandler) which has the following form.

~~~~{.cpp}

void MyGame::ResultHandler(eErrorCode code, const CCloudResult *result) {
	const CHJSON *json = result->GetJSON();
}

~~~~

This object is guaranteed never `NULL` (at worst it is empty). You can read from `CHJSON` objects in a safe and compact way using this recommended set of methods.

`bool CotCHelpers::CHJSON::Has(const char *key) const`<br/>
`const CHJSON* CotCHelpers::CHJSON::Get(int aIndex) const`<br/>
`const CHJSON* CotCHelpers::CHJSON::Get(const char *aItem) const`<br/>
`const CHJSON* CotCHelpers::CHJSON::GetSafe(int aIndex) const`<br/>
`const CHJSON* CotCHelpers::CHJSON::GetSafe(const char *aItem) const`<br/>
`double CotCHelpers::CHJSON::GetDouble(const char *aItem, double defaultValue) const`<br/>
`int CotCHelpers::CHJSON::GetInt(const char *aItem, int defaultValue) const`<br/>
`bool CotCHelpers::CHJSON::GetBool(const char *aItem, bool defaultValue) const`<br/>
`const char* CotCHelpers::CHJSON::GetString(const char *key, const char *defaultValue) const`<br/>
`Iterator CotCHelpers::CHJSON::begin() const`<br/>
`Iterator CotCHelpers::CHJSON::end() const`<br/>
`int CotCHelpers::CHJSON::size() const`<br/>

If you expect to have an object such as {"obj": {"value": 123}} then you can safely do the following.

~~~~{.cpp}

void MyGame::ResultHandler(eErrorCode code, const CCloudResult *result) {
	const CHJSON *json = result->GetJSON();
	int value = json->GetSafe("obj")->GetInt("value");
	// Value will be either 0 (either json is empty, obj doesn't exist or value doesn't exist) either the desired value
}

~~~~

It will work because all `Get*` methods (except CotCHelpers::CHJSON::Get itself which might return `NULL`) will safely handle the fact that the desired object does not exist and return a default value. In the case of CotCHelpers::CHJSON::GetSafe it is simply an empty object (see CotCHelpers::CHJSON::Empty) so you may transitively query for additional keys within the hierarchy without worrying.

Optionally, you can also pass a default value to the `Get*` methods, which will be returned in case the element is not found.

Listing the sub-nodes ("values") of a `CHJSON` can be done easily using the provided iterator. 

~~~~{.cpp}

CHJSON *object = new CHJSON;
object->Put("key1", "value1");
object->Put("key2", "value2");

for (const CHJSON *node: *object) {
	const char *key = node->name();
	printf("Key: %s, value: %s\n", key, object->GetString(key));
}
delete object;

~~~~

This can be done for arrays as well, but nodes obviously won't have a name. This snippet is provided here for reference:

~~~~{.cpp}

CHJSON *array = CHJSON::Array();
array->Add(new CHJSON(123));
for (const CHJSON *node: *array) {
	if (node->type() == CHJSON::jsonNumber)
		printf("Got a number: %d", node->valueInt());
}

~~~~

Using callbacks (CResultHandler)
===========

The CloudBuilder SDK uses a strongly asynchronous programming model, with callbacks and listeners in many places to process data coming from the network. To achieve that, the model relies on a class named `CDelegate`, which basically allows to pass a pointer to a method with a given signature to be executed later when the arguments have become available. For reference, here is a sample of game requiring you to guess a number, with the method to check being passed as argument:

~~~~{.cpp}

struct MyGame {
	void Main(int argc, char *argv[]) {
		// We'll accept the inputted number if it is odd, easy enough!
		Play(MakeDelegate(this, &MyGame::IsOdd));
	}

	void Play(CDelegate<bool (int)> *checkFunc) {
		int inputtedNumber;
		do {
			printf("Input a number: ");
			scanf("%d", &inputtedNumber);
		} while (!checkFunc->Invoke(inputtedNumber));
		delete checkFunc;
	}

	bool IsOdd(int number) {
		return number % 2 == 0;
	}
}

~~~~

The same principle is used with `CResultHandler`, which is actually just a kind of `CDelegate` with standard arguments. Usually, you will want to create result handlers by using the provided MakeResultHandler method:

~~~~{.cpp}
void MyGame::OnSetup(eErrorCode code, const CCloudResult *result);

CClan::Instance()->Setup(&json, MakeResultHandler(this, &MyGame::OnSetup));
~~~~

It will create the appropriate type of delegate using genericity, and the Setup method will not accept it if the type differ, meaning that you will have to fix the signature of your OnSetup method to match the expected one.

Passing parameters
---------

The `MakeResultHandler` allows you to pass additional parameters, which will be forwarded to your method as additional arguments trailing the default ones. An example is shown below.

~~~~{.cpp}
void MyGame::OnSetup(eErrorCode code, const CCloudResult *result, int additionalInt, char *additionalStr) {
	printf("Got %d and %s\n", additionalInt, additionalStr);
	free(additionalStr);
}

CClan::Instance()->Setup(&json, MakeResultHandler(this, &MyGame::OnSetup, 123, strdup("hello")));
~~~~

You can pass up to 3 parameters of any type, even a struct if you like. However, on a performance point of view, keep in mind that the parameters may be copied multiple times around, so it is peferrable to use either small and simple structures or pass a pointer. Also note that if you pass a pointer to something, it has to remain valid until the callback is called, so you will probably want to duplicate the object and delete it inside the callback as shown above with the strdup/free combo.

Custom delegates
---------

Using polymorphism, it is also possible to make fully custom callbacks, which just have to respond to the specification of a `CDelegate` (that is, basically to provide an object/method combo corresponding to the signature, to be invoked). Anonymous structures come in handy for this task:

~~~~{.cpp}

struct SetupHandler: CResultHandler {
	SetupHandler() : CResultHandler(this, &SetupHandler::Done) {}
	
	void Done(eErrorCode code, const CCloudResult *result) {
		// Inline ("lambda"-style) processing
	}
};

CClan::Instance()->Setup(&json, new SetupHandler);

~~~~

The only problem here is that your anonymous structure doesn't have access to the enclosed members. You need to capture them manually, as shown below for the `this` pointer.

~~~~{.cpp}

struct MyGame {
	
	void Main(int argc, char *argv[]) {
		struct SetupHandler: CResultHandler {
			MyGame *self;
			SetupHandler(MyGame *self) : self(self), CResultHandler(this, &SetupHandler::Done) {}
			void Done(eErrorCode code, const CCloudResult *result) {
				// Inline ("lambda"-style) processing
				self->SetupOkay();
			}
		};

		CClan::Instance()->Setup(&json, new SetupHandler(this));
	}
	
	void SetupOkay() {
	}
}

~~~~

However, now that you know the inners of these delegates, you can forward the original call anywhere you like. You may for instance forward the call to a C++11 lambda as shown below, enabling for very nice constructs.

~~~~{.cpp}
#include <functional>

typedef std::function<void(eErrorCode, const CCloudResult*)> resultHandler_t;

static CResultHandler *MakeResultHandler(resultHandler_t func) {
	struct FunctionalResultHandler: CResultHandler {
		resultHandler_t func;
		FunctionalResultHandler(resultHandler_t func) : func(func), CResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result) {
			func(code, result);
		}
	};
	return new FunctionalResultHandler(func);
}

struct MyGame {
	
	void Main(int argc, char *argv[]) {
	
		CClan::Instance()->Setup(&json, MakeResultHandler([=] (eErrorCode code, const CCloudResult *result) {
			this->SetupOkay();
		}));
	}
	
	void SetupOkay() {
	}
};

~~~~

If you are using Visual C++ 2010, beware that there is a bug preventing nested lambdas from capturing the same member in this version.
