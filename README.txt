About ABT

ABT (Access by Term) is a module that controls node access based on relationship between node->term<-user where taxonomy terms allow for hierarchical content access control.

----------------
| Installation |
----------------
Install & enable.

---------
| Usage |
---------
1. After enabling the module, make sure you set appropriate permissions for your roles.
2. Add some taxonomy terms in the vocabularies you intent to use. Do not forget to think hierarchically. ABT handles access inheritance in such way that parent has equal or greater access then it's child.
3. Create fields:
  - Add a "Term reference" field instance to the content type(s) you want to control.
  - Add a "Term reference" field instance to the user.
  - ABT has support for multiple access flags, so you may set the field instances to "unlimited" values, if you need. When editing/adding settings for the field instance, pick the type of access to control by checking any or all of the flags view/update/delete. If you check any of these, access for this content type will be controlled by ABT. If none are checked, this remains a regular field. Let's say you check only "delete" flag. This would mean you want to control the "delete" access with the field. Other two unchecked boxes will result in "access denied".
    If your setup requires, you can create any number of different fields (with different vocabularies attached) and have each control one of the flags (view/update/delete). It's completely up to you how you set it up. If you ame to use more then one field per content type - It is your responsibility to make sure that there fields controlling are not overlapping (For example: field A and field B are both set to control view-access for content type Articles - this could have unexpected results).

4. "Tag" nodes with appropriate access terms.
5. "Tag" users with appropriate access terms.
