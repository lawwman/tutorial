## **TLDR**
Sentinel value seems to have varying meanings according to different sources. It could indicate:

- special value to indicate termination of a process
- special value to indicate premature end to a process
- special value to indicate 'not found' scenario (in python, `None` is commonly used as this 'not found' value)

## **Wiki notes**
Sentinel value is a special value used to indicate the **termination of a process**, typically a loop or recursion. This sentinel value should be chosen to be clearly distinct from the set of legal values to be returned.

Examples:

- Null pointer at the end of a linked list
- When reading a string, if "#" is predetermined to signal the end of the string, "#" is the sentinel value.

Often related to the [Semipredicate problem](https://en.wikipedia.org/wiki/Semipredicate_problem)

## **From this [article](https://python-patterns.guide/python/sentinel-object/)**
what I noticed is that they also use sentinel value to indicate when something is **not found**. For example: `str.find()` is used to return the index of the char you want. If it cannot find it, it returns the sentinel value, -1.

They also talk about Null Object pattern, which is quite interesting. Imagine a list of Employee objects, and you want to print the employee's manager's name variable in each object with the following code

```
for e in employees:
    if e.manager is None:
        m = 'no one'
    else:
        m = e.manager.display_name()
    print(e.name, '-', m)
```
An alternative is to use `NO_MANAGER = Person(name='no acting manager')` to act in place of the `None` object. We can then remove the `if-else` conditions, making the code much cleaner.