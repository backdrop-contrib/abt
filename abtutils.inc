<?php
/**
 * @file abtutils.inc
 * File containing AbtUtils class.
 */

/**
 * Static class containing utility methods for the ABT module.
 * 
 */
class AbtUtils {

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
    if(property_exists($first_term_data,'vid')) {
      $vid = intval($first_term_data->vid);
    } else {
      return $out;
    }
    unset($first_term_data);

    foreach ($terms as $tkey => $term) {
      $out[$term['tid']] = $term['tid'];
      $children = taxonomy_get_tree($vid, $term['tid']);
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
