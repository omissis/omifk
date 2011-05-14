<?php

/* vim: set expandtab tabstop=2 shiftwidth=2 softtabstop=2: */

/**
 * Base Omifk library
 *
 * PHP version 5.2
 *
 * @category Frameworks
 * @package  Omifk
 * @author   Claudio Beatrice <claudi0.beatric3@gmail.com>
 * @license  http://www.php.net/license/3_01.txt  PHP License 3.01
 * @version  SVN: $Id$
 * @link     http://www.silent-voice.org/
 */

/**
 * Detect whether the current script is running in a command-line environment.
 */
function omifk_is_cli() {
  return (!isset($_SERVER['SERVER_SOFTWARE']) && 
    (php_sapi_name() == 'cli' || (is_numeric($_SERVER['argc']) && $_SERVER['argc'] > 0)));
}