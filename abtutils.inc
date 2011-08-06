<?php
/**
 * @file abtutils.inc
 * File containing AbtUtils class.
 */

/**
 * Static class containing utility methods for the ABT module.
 * 
 * This class is static and as such, should not be instantiated.
 */
class AbtUtils {

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
  public static function createFieldInstance($field_name, $field_title, $entity_type, $bundle) {
    if (!$instance = field_info_instance($entity_type, $field_name, $bundle)) {
      $instance = array(
        'field_name' => $field_name,
        'entity_type' => $entity_type,
        'label' => $field_title,
        'bundle' => $bundle,
      );
      try {
        $instance = field_create_instance($instance);
      } catch (FieldException $ex) {
        drupal_set_message(t('ABT: Field instance could not be created. It might exist already? %msg', 
          array('%msg' => $ex->getMessage())));
        return FALSE;
      }
    }
    return $instance;
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
    $first_term_data = taxonomy_term_load($terms[0]['tid']);
    for($i = 0; $i < count($terms); $i++) {
    #foreach ($terms as $tkey => $term) {
      $out[$terms[$i]['tid']] = $terms[$i]['tid'];
      $children = taxonomy_get_tree($first_term_data->vid, $terms[$i]['tid']);
      foreach ($children as $ckey => $child) {
        $out[$child->tid] = $child->tid;
      }
    }
    return $out;
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
  public static function grantConstruct($nid, $realm, $gid, $v, $u, $d, $priority = 1) {
    return array(
      'nid' => $nid,
      'realm' => $realm, 
      'gid' => $gid, 
      'grant_view' => $v, 
      'grant_update' => $u, 
      'grant_delete' => $d, 
      'priority' => $priority,
    );
  }
}
