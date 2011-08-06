About ABT

ABT (Access by Term) is a module that controls access based on relationship between node->term<-user where taxonomy terms allow for an hierarchical access control.

In this document, sometimes taxonomy terms will be referenced as groups. I am hoping that this will help explaining how ABT works.


----------------
| Installation |
----------------
*Install & enable.

---------
| Setup |
---------
When creating/editing a field of type "Term reference" you will get to see an ACCESS BY TERM control area. Here you can enable/disable node access control for view/update/delete. 

---------
| Usage |
---------
1. Add some taxonomy terms in the vocabularies you intent to use. Do not forget to think hierarchically. ABT handles access inheritance in such way that parent has equal or more access then it's child.
2. Add a "Term reference" field instance to the content types you want to control.
3. Add a "Term reference" field instance to the user.
2. When editing/adding the field instance, pick the type of access to control (view/update/delete).
3. "Tag" users with appropriate access terms/groups.
4. "Tag" nodes with appropriate access terms/groups.

