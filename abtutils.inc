<?php
/**
 * @file abtutils.inc
 * File containing AbtUtils class.
 */

/**
 * Static class containing utilities for the ABT module.
 * 
 * This class is static and as such, should not be instantiated.
 */
class AbtUtils {

  /** 
   * Static property used as a mashine name of the 
   * vocabulary where we store the VIEW access terms.
   * 
   * It is also used as the name of the drupal variable 
   * stored in the database. Variable stored in the 
   * database holds the vocabulary id (vid).
   * 
   * @var string
   */
  public static $vocViewAccess = 'abt_view_access';
  
  /** 
   * Static property used as a mashine name of the 
   * vocabulary where we store the UPDATE access terms.
   * 
   * It is also used as the name of the drupal variable 
   * stored in the database. Variable stored in the 
   * database holds the vocabulary id (vid).
   * 
   * @var string
   */
  public static $vocUpdateAccess = 'abt_update_access';
 
  /** 
   * Static property used as a mashine name of the 
   * vocabulary where we store the DELETE access terms.
   * 
   * It is also used as the name of the drupal variable 
   * stored in the database. Variable stored in the 
   * database holds the vocabulary id (vid).
   * 
   * @var string
   */
  public static $vocDeleteAccess = 'abt_delete_access'; 
 
  /** 
   * Static property used as a term reference field name 
   * 
   * @var string
   */
  public static $fieldAccessView = 'field_abt_access_view';
  
  /**
   * Static property used as a term reference field name 
   * 
   * @var string
   */
  public static $fieldAccessUpdate = 'field_abt_access_update';
  
  /**
   * Static property used as a term reference field name 
   * 
   * @var string
   */
  public static $fieldAccessDelete = 'field_abt_access_delete';
  
  /** 
   * Static private property used for definition of
   * the language used when setting and getting terms.
   * 
   * @var string
   */
  private static $lang = 'und';

  /** 
   * Method for creating field instances.
   * 
   * @param string $field_name
   *    Field name to use for instantiating.
   * @param string $field_title
   *    Name for the the new field.
   *
   * @return Array on success, FALSE on failure.
   *    Returns the newly created instance or FALSE if 
   *    the instance could not be created.
   */
  public static function createFieldInstance($field_name, $field_title) {
    if (!$instance = field_info_instance('node', $field_name, 'abt')) {
      $instance = array(
        'field_name' => $field_name,
        'entity_type' => 'node',
        'label' => $field_title,
        'bundle' => 'abt',
      );
      try {
        $instance = field_create_instance($instance);
      } catch (FieldException $ex) {
        drupal_set_message(t('ABT: Will be using old instance of the field %field_name: %msg.', 
          array('%field_name' => $instance['label'], '%msg' => $ex->getMessage())));
        return FALSE;
      }
    }
    return $instance;
  }
  
  /** 
   * Method for creating vocabularies.
   * 
   * @param string $v_name
   *    Human readable name of the vocabulary.
   * @param string $v_description
   *    Description of the vocabulary.
   * @param string $v_machine_name
   *    Name of the vocabulary that will be stored in the database.
   */
  public static function createVocabulary($v_name, $v_description, $v_machine_name) {
    if (!$voc_r = taxonomy_vocabulary_load(variable_get($v_machine_name, 0))) {
      $vocabulary = array(
        'name' => $v_name, 
        'description' => $v_description, 
        'machine_name' => $v_machine_name, 
        'multiple' => 1, //set 1 for multiple selection
        'required' => 0, //set 1 to make the terms mandatory to be selected
        'hierarchy' => 1, //set 1 to allow and create hierarchy of the terms within the vocabulary
        'relations' => 1, //set 1 to set and allow relation amongst multiple terms
        //'module' => 'abt', //provide the module name in which the vocabulary is defined and which is calling this function
        //'nodes' => array('abt' => 1), //set the node to which this vocabulary will be attached to
        'weight' => -9, //set the weight to display the vocabulary in the list
      );
      $vocabulary = (object) $vocabulary;
      taxonomy_vocabulary_save($vocabulary);
      variable_set($v_machine_name, $vocabulary->vid); // vid apears magicaly after we save the object :)
    }
  }
  
  /** 
   * Method for creating taxonomy term references.
   * 
   * @param string $field_name
   *    Name for the field. Must be unique.
   * @param string $v_machine_name
   *    Machine name of the holding vocabulary.
   * 
   * @return TRUE on success, FALSE on failure.
   */  
  public static function createTermReference($field_name, $v_machine_name) {
    if (!$field = taxonomy_vocabulary_load(variable_get($field_name, 0))) {
      $field = array(
        'field_name' => $field_name,
        'type' => 'taxonomy_term_reference',
        'settings' => array(
          'allowed_values' => array(
            array(
              'vocabulary' => $v_machine_name,
              'parent' => 0,
            ),
          ),
        ),
      );
      try {
        $created = TRUE;
        $field = field_create_field($field);
      } catch (FieldException $ex) {
        $created = FALSE;
        drupal_set_message(t('ABT: Could not create taxonomy_term_reference (%field_name): %msg.', 
          array('%field_name' => $field_name, '%msg' => $ex->getMessage())));
      }
      if ($created) {
        variable_set($field_name, $field['id']);
        return TRUE;
      }
    }
    return FALSE;
  }
  
  
  /** 
   * Method for deleting vocabularies.
   * 
   * @param string $v_machine_name
   *    Machine name of the vocabulary you wish to delete.
   */  
  public static function deleteVocabulary($v_machine_name) {
    // Fetch the vocabulary id from the database, if any
    if ($vid = variable_get($v_machine_name)) {
      // Delete the vocabulary
      taxonomy_vocabulary_delete($vid);
      // Remove the variable stored in the database
      variable_del($v_machine_name);
    }
  }
  
  /** 
   * Method for deleting taxonomy term references.
   * 
   * @param string $field_name
   *    Name for the field you wish to delete.
   */  
  public static function deleteField($field_name) {
    if (field_info_field($field_name)) {
      field_delete_field($field_name);
    }
  }

  /** 
   * Method for deleting field instances.
   * 
   * @param string $field_name
   *    Fieldname of the instance you wish to delete.
   * @param boolean $cleanup
   *    (optional) Set to TRUE if you want to remove 
   *    all data associated with this instance.
   * @param string $type
   *    (optional) Type of the instance you wish to delete.
   */    
  public static function deleteFieldInstance($field_name, $cleanup = TRUE, $type = 'node') {
    if ($instance = field_info_instance($type, $field_name, 'abt')) {
      field_delete_instance($instance, $cleanup);
    }
  }


  /** 
   * Method for fetching taxonomy term data for a group of terms.
   * 
   * @param Array $term_array
   *    Array of terms. Each term must have the index "tid"
   *    where it stores the id of term you wish to fetch.
   *
   * @return Array
   *    On success returns array of terms with all their data.
   *    On failure returns an empty array.
   *    
   */    
  public static function getTermData($term_array) {
    $out = array();
    if (empty($term_array) || !is_array($term_array)) {
      return $out;
    }
    foreach ($term_array as $term) {
      $out[$term['tid']] = taxonomy_term_load($term['tid']);
    } 
    return $out;
  }
  
  /** 
   * Method for fetching all of the children for a taxonomy 
   * term or an array of taxonomy terms.
   * 
   * @param string $terms
   *    Array of terms. Each term must be an object containing 
   *    properties tid, vid & name.
   *
   * @return Array
   *    On success returns array of terms with all their children.
   *    On failure returns an empty array.
   *    
   */ 
  public static function taxonomyGetChildrenAll($terms) {
    $out = array();
    if (empty($terms) || !is_array($terms)) {
      return $out;
    }
    foreach ($terms as $tkey => $term) {
      $out[$term->tid] = $term->name;
      $children = taxonomy_get_tree($term->vid, $term->tid);
      foreach ($children as $ckey => $child) {
        $out[$child->tid] = $child->name;
      }
    }
    return $out;
  }
  
  /**
   * Method for fetching all of the ancestors for a single 
   * taxonomy term, or an array of taxonomy terms.
   * 
   * @param Array $terms
   *    Array of terms. Each term must be an object containing 
   *    properties tid, vid & name.
   *
   * @return Array
   *    On success returns array of terms with all their children.
   *    On failure returns an empty array.
   *    
   */ 
  public static function taxonomyGetParentsAll($terms) {
    $out = array();
    if (empty($terms) || !is_array($terms)) {
      return $out;
    }
    foreach ($terms as $tkey => $term) {
      $out[$term->tid] = $term->name;
      $parents = taxonomy_get_parents_all($term->tid);
      foreach ($parents as $pkey => $parent) {
        $out[$parent->tid] = $parent->name;
      }
    }
    return $out;
  }

  /** 
   * Method for fetching the language abbreviation that was used
   * when creating the taxonomy term.
   *
   * This method is here as a percaution for the future 
   * development of this module.
   *
   * @param int $tid
   *    (optional) Taxonomy term id.
   *
   * @return string
   *    The language abbreviation.
   *    
   */   
  public static function getTermLang($tid = 0) {
    return self::$lang;
  }

  /** 
   * Method for constructing the grant array, used when creating grants 
   * to write to node_access table.
   *
   *
   * @param int $nid
   *    Node id.
   * @param int $gid
   *    Grant id. This can be an id for pretty much anything. In this module
   *    it is used to store the taxonomy term id.
   * @param int $v
   *    Allow view. 1 is for TRUE, 0 is for FALSE.
   * @param int $u
   *    Allow update. 1 is for TRUE, 0 is for FALSE.
   * @param int $d
   *    Allow delete. 1 is for TRUE, 0 is for FALSE.
   * @param int $priority
   *    (optional) priority for this grant. The higher, the more important.
   * 
   * @return Array
   *    Grant constructed and ready for baking.
   *    
   */
  public static function grantConstruct($nid, $gid, $v, $u, $d, $priority = 1) {
    return array(
      'nid' => $nid,
      'realm' => 'abt', 
      'gid' => $gid, 
      'grant_view' => $v, 
      'grant_update' => $u, 
      'grant_delete' => $d, 
      'priority' => $priority,
    );
  }
}
