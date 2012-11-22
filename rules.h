/*
 Rules - Simple rule based system in C for integers.
 BSD license.
 by Sven Nilsen, 2012
 http://www.cutoutpro.com
 
 Version: 0.000
 Angular degrees version notation
 http://isprogrammingeasy.blogspot.no/2012/08/angular-degrees-versioning-notation.html
 
 */
/*
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 */
/*
 
 RULE BASED SYSTEM
 
 Sometimes you might want to attack a problem from abstract view of point.
 A rule based systems creates and processes rules which maps a set of targets
 to a result. 
 
 One way to think this way is that for each rule is a quantity of knowledge 
 about a system, therefore the problem should be easier to solve if you can
 reduce it down to simpler rules. It is meant to assist you while finding
 the solution
 
 A rule system is like a very simple programming language that fits into
 a template algorithm. For example, a programming language parser would
 have no use of a full scripting environment since that is exactly what
 it attempts to fullfill. This is a situation where rule based system can
 simplify the source code.
 
 A rule system is appreciated also as an abstract model, by having a complete
 example of it you can look it up and see if the problem is solvable by it.
 
 The following keywords can be used to create rules without depending on
 the internal mechanics of the rule system.
 
 ACTION
 
 An 'action' is just a naming convention for keeping systems
 separate, in order to store the all rules in same system without mixing them.
 Since this is often associated with directions or relations, the name
 of an action often reflects common used words.
 
	left
	right
	up
	down
 
 VALUE
 
 A 'value' is a number representing the 'object' of the rule.
 Since a number can point to any object, this is a nice way to categorize rules.
 A value of -1 refers to 'any object' so the rule is triggered for all numbers.
 The value is referred to as the 'source' of the rule.
 
 TARGET
 
 A 'target' is a number refering to the subject of the rule.
 The template algorithm loops through a collection, picks a target and checks
 the rules.
 
	any							any number
 
	number						the number specified in 'options'
 
	next						the next number after 'value'
 
	previous					the previous number before 'value'
 
	less						less than specified in 'options'
 
	less or equal				less or equal than specified in 'options'
 
	greater						greater than specified in 'options'
 
	greater or equal			greater or equal than specified in 'options'
 
 RESULT
 
 A 'result' is the type of action to perform after target has been detected.
 
	source						returns the source
 
	target						returns the target
 
	sum							add source and target
 
	difference from source		return source - target
 
	difference from target		return target - source
 
	difference from options		return options - target
 
	product						multiply target with options
 
	division					divide target with options
 
	options						return the options
 
	modulus						take modulus of target with options
								this is often used in combination with
								target 'next' and 'previous' to map indices
								correctly to the range of an array.
	nothing						returns -1
 
 */
#ifndef RULES_GUARD
#define RULES_GUARD

// Stores the data about the rule.
typedef struct rule
{
	int action;
	int target;
	int result;
	int value;
	int options;
} rule;

void rules_test(void);

// Processes one rule. If it did not work, it returns -1.
int rules_ProcessRule(rule *r, int action, int source, int target);

// Returns a new rule created from strings.
rule rules_CreateRule
(const char *action, const char *target, const char *result,
 int value, int options);

#endif

#ifndef FUNC_GUARD
#define FUNC_GUARD
#define func(ns, n) static __typeof(ns##_##n) * const n = ns##_##n
#endif
