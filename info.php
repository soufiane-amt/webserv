<?php
  echo exec('./program');
  for ($i = 0; $i < 1000000; $i++) {
    $out =  exec('ls');
    echo $out;
  }
?>
