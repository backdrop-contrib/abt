Access by Term (ABT)
====================

Access by Term (ABT) is a module that controls node access based on relationship between node->term<-user where taxonomy terms allow for hierarchical content access control.

- Supports the following permissions:
  - View
  - Update
  - Delete 
- Grants are based on the relationship between the user->term<-node.
- Taxonomy terms act as common denominators and allow many-to-many relationships between users and nodes.
- Organize your taxonomy terms hierarchically, this approach will allow for access grant inheritance.
- Nodes found in Views are also filtered out when user lacks permissions.
- Very simple, easy to understand logic and very little code. Uses lots of native functionality.
- Use any number of fields/vocabularies to control access for any number of content types.
- Has it's own automated tests. (Note: in Drupal, not converted for Backdrop)

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules.

Usage
-----
1. After enabling the module, make sure you set appropriate permissions for your roles.
2. Add some taxonomy terms in the vocabularies you intent to use. Do not forget to think hierarchically. ABT handles access inheritance in such way that parent has equal or greater access then it's child.
3. Create fields:
  - Add a "Term reference" field instance to the content type(s) you want to control.
  - Add a "Term reference" field instance to the user.
  - Configure ABT in the field instance form. ABT has support for multiple access permissions, so you may set the field instances to "unlimited" values, if you need. When editing/adding settings for the field instance, pick the type of access to control by selecting any or all of the fields to control view/update/delete access. If you check any of these, access for this content type will be controlled by ABT. If none are checked, this remains a regular field. Let's say you check only "delete" permission. This would mean you want to control the "delete" access with the field. Other two unchecked boxes will result in "access denied".
  - If your setup requires, you can create any number of different fields (with different vocabularies attached) and have each control one of the access permissions (view/update/delete). It's completely up to you how you set it up. If you aim to use more than one field per content type, it is your responsibility to make sure that there fields controlling are not overlapping (For example: field A and field B are both set to control view-access for content type Articles - this could have unexpected results).
4. "Tag" nodes with appropriate access terms.
5. "Tag" users with appropriate access terms.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

Maintainers
-----------
- Alex Höbart (https://github.com/AlexHoebart-ICPDR)

Originally written for Drupal by
- ado b (adooo) (https://www.drupal.org/u/adooo)

This module is seeking additional maintainers.
