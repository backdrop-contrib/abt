About ABT
ABT (Access by Term) is a module that controls access based on relationship between node->term<-user where taxonomy terms allow for an hierarchical access control.
In this document, sometimes taxonomy terms will be referenced as groups. I am hoping that this will help explaining how ABT works.

Installation
  Install & enable.

Setup
  * Step 1:
    Go to Taxonomy panel and you should be able to see two vocabularies in the list:
       1. View Access by Term vocabulary is used to hold the groups (terms) that are permitted view access to your nodes.
       2. Update Access by Term vocabulary is used to hold the groups (terms) that are permitted update access to your nodes.
       3. Delete Access by Term vocabulary is used to hold the groups (terms) that are permitted delete access to your nodes.
    Note: ABT module needs to be installed and enabled for these vocabularies to show.

  * Step 2:
    Go to Account fields management and use Add existing field to add a term reference to user accounts. When selecting the field you will see three fields that belong to ABT module:
       1. field_abt_access_view is used for setting the view access to you nodes.
       2. field_abt_access_update is used for setting the update access to you nodes.
       3. field_abt_access_delete is used for setting the delete access to you nodes.
    Add all three if you want to control view/update/delete aspects of your nodes. Depending on you needs you might consider allowing users to be part of more then one group (taxonomy term). In this case you can choose select box as the widget and allow multiple selections.

    Here you can also set the default values for the users access permission.

  * Step 3:
    Go to Content types management and proceed with any content type you want to control access to. Click on the manage fields of the ontent type you want to work with. 

    As in the previous step, you want to add fields using the Add existing field functionality. Just like before, you will see three fields that belong to ABT module:
       1. field_abt_access_view is used for setting the view access for your user.
       2. field_abt_access_update is used for setting the update access for your user.
       3. field_abt_access_delete is used for setting the delete access for your user.
    Depending on you needs you might consider allowing nodes to be connected to more then one group (taxonomy term). In this case you choose select box as the widget and allow multiple selections.

    Here you can also set the default values for nodes.


Usage
  By now you should be set to go:
    * Add some taxonomy terms in the vocabularies you intent to use. Do not forget to think hierarchically.
    * Add/edit user an old assigning him/her appropriate access terms.
    * Add/edit content and assign appropriate access terms.

  ABT handles access hierarchy in such way that parent has equal or more access then it's child. 
