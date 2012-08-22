<?php
/**
 * Implement hook_form().
 */
function group_list_user() {
  $group_id = $_POST['id'];

  $query = db_query('SELECT
                  users.uid AS uid,
                  users.name AS users_name,
                  og_uid.uid AS og_uid_uid,
                  og_uid.nid AS og_uid_nid,
                  og_uid.is_active AS og_uid_is_active,
                  og_uid.is_admin AS og_uid_is_admin
            FROM 
                  users users 
            LEFT JOIN 
                  og_uid og_uid ON users.uid = og_uid.uid
            WHERE 
                  (users.status <> 0) AND (og_uid.nid = %d )
            ORDER BY 
                  og_uid_is_admin DESC, og_uid_is_active ASC, users_name ASC',$group_id);
  $header = array(
    array('data' => t('No')),
    array('data' => t('Name')),
    array('data' => t('Edit')),
    array('data' => t('Delete')),
    array('data' => t('Add term')),
  );
  $i = 1;
  while($row = db_fetch_array($query)) {
     $rows[] = array(
        $i,
        l($row['users_name'], '/user/'.$row['uid']),
        l(t('Edit'), '/user/'.$row['uid'].'/edit'),
        l(t('Delete'), '/user/'.$row['uid'].'/delete'),
        array('data' => l(t('Add term'), 'group_list_taxonomy_list', array('query' => 'id='.$row['uid'])) , 'class' => 'term-link'),
    );
    $i++;
  }

  if (!isset($rows)) {
    $rows[] = array(array('data' => t('No groups available.'), 'colspan' => 4));
  }

  $output = theme('table', $header, $rows);
  
  print $output;
}

function group_list_taxonomy_list_callback() {
  $parentname = $_POST['parentname'];
  $childname = $_POST['childname'];
  $parentId = $_POST['parentId'];
  $childId = $_POST['childId'];
  $userId = $_POST['userId'];
  if($_POST['action'] == 'save') {
    $query = db_result(db_query("SELECT COUNT(*) FROM {term_user} WHERE uid = %d AND tid = %d", $userId, $childId));
   
    if($query == 0) {
      $query = "INSERT INTO {term_user} (uid, tid) VALUES (%d, %d)";
      db_query($query, $userId, $childId);
      $output .= '<tr><td>';
      $output .= '<span class="dropbox-item">'.$parentname.'</span><span class="hierarchical-select-item-separator">›</span>';
      $output .= '<span class="dropbox-item dropbox-selected-item">'.$childname.'</span>';
      $output .= '</td>';
      $output .= '<td class="dropbox-remove"><div id="taxonomy-remove" onclick="remove()">Remove</div></td></tr>';
    }
    else {
      $output = '<td>This term is already assign.</td>';
    }

  }
  else {
    db_query('DELETE FROM {term_user} WHERE uid = %d AND tid = %d' , $userId, $childId);
    $output = '<td>Nothing has been selected.</td>';
  }
  print $output;
}

function group_list_taxonomy_ajax() {

  $vid = $_POST['id'];

  $header = array(
    array('data' => t('No')),
    array('data' => t('Term name')),
    //array('data' => t('Edit')),
    //array('data' => t('Delete')),
  );
  $i = 1;
  foreach(taxonomy_get_tree($vid) as $values) {
     $rows[] = array(
        $i,
        l($values->name, 'term/'.$values->tid),
      //  l(t('Edit'), 'admin/content/taxonomy/edit/term/'.$values->tid),
      //  l(t('Delete'), 'group_list/delete/term/'.$values->tid),
    );
    $i++;
  }

  if (!isset($rows)) {
    $rows[] = array(array('data' => t('No groups available.'), 'colspan' => 4));
  }

  $output = theme('table', $header, $rows);
  
  print $output;  
}
