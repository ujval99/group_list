$(document).ready(function() {

  $("#edit-all-groups").change(function () {
            var id=$(this).val();
            var dataString = 'id='+ id;
          $.ajax
            ({
              type: "POST",
              url: "?q=group_list_ajax",
              data: dataString,
              success: function(html)
              {
                $("div#group_list").html(html);
                timeout_dealy();
              }
          });

  })
  .change();

  $("#edit-all-taxonomy").change(function () {
            var id=$(this).val();
            var dataString = 'id='+ id;
          $.ajax
            ({
              type: "POST",
              url: "?q=group_list_taxonomy_ajax",
              data: dataString,
              success: function(html)
              {
                $("div#taxonomy_group_list").html(html);
              }
          });

  })
  .change();

  $('#submit-form').click(function () {
    var parent = $("#edit-tid-hierarchical-select-selects-0 option:selected").text();
    var parentId = $("#edit-tid-hierarchical-select-selects-0 option:selected").val();
    var child = $("#edit-tid-hierarchical-select-selects-1 option:selected").text();
    var childId = $("#edit-tid-hierarchical-select-selects-1 option:selected").val();
    var userId = $("div#user-uid").html();
    var dataString = 'parentname=' + parent + '&childname=' + child + '&parentId='  + parentId + '&childId='  + childId + '&userId='  + userId + '&action=save';
    $.ajax
      ({
        type: "POST",
        url: "?q=group_list_taxonomy_list/callback",
        data: dataString,
        success: function(html)
        {
          if($(".dropbox-is-empty").children('td').length == 1) {
            $(".dropbox-entry").html(html);
          } else {
            var parentHeight = window.parent.$('#outerImageContainer').height();
            window.parent.$('#outerImageContainer').attr('style', 'height:' + (parentHeight+30) + 'px !important');
            window.parent.$('#outerImageContainer').width(620);
            $(".dropbox-entry").append(html);
          }
        }
    });
  });

});

function remove() {
  var parent = $("#edit-tid-hierarchical-select-selects-0 option:selected").text();
  var parentId = $("#edit-tid-hierarchical-select-selects-0 option:selected").val();
  var child = $("#edit-tid-hierarchical-select-selects-1 option:selected").text();
  var childId = $("#edit-tid-hierarchical-select-selects-1 option:selected").val();
  var userId = $("div#user-uid").html();
  var dataString = 'parentname=' + parent + '&childname=' + child + '&parentId='  + parentId + '&childId='  + childId + '&userId='  + userId + '&action=delete';
  $.ajax
  ({
    type: "POST",
    url: "?q=group_list_taxonomy_list/callback",
    data: dataString,
    success: function(html)
    {
      $(".dropbox-entry").html(html);
    }
  });
}

function timeout_dealy() {
  setTimeout(function() {
    $(".sticky-enabled > tbody > tr > td.term-link > a").each(function() {
      $(this).attr("href", $(this).attr("href"));
      $(this).attr("rel", "lightframe");
    });
    Lightbox.initList();
  }, 500);
}
