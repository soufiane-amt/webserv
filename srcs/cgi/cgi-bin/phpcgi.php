<!-- /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phpcgi.php                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:38:55 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/26 22:38:56 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ -->

<?php

//$GLOBALS PHP Superglobal test
// $x = 75;
// $y = 25;
 
// function addition() {
//   $GLOBALS['z'] = $GLOBALS['x'] + $GLOBALS['y'];
// }
 
// addition();
// echo $z;

echo $_SERVER['PHP_SELF'];
echo "<br>";
echo $_SERVER['SERVER_NAME'];
echo "<br>";
echo $_SERVER['HTTP_HOST'];
echo "<br>";
echo $_SERVER['HTTP_REFERER'];
echo "<br>";
echo $_SERVER['HTTP_USER_AGENT'];
echo "<br>";
echo $_SERVER['SCRIPT_NAME'];

?>