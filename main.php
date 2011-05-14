<?php

/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * Index file
 *
 * This file contains the entry point for the framework
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

 /** Define path to application directory */
defined('OMIFK_APPLICATION_PATH')
  || define('OMIFK_APPLICATION_PATH', realpath(__DIR__) . '/');

/** Setting the include path */
set_include_path(implode(PATH_SEPARATOR, array(
  realpath(OMIFK_APPLICATION_PATH . '/lib/vendors'),
  get_include_path()
)));

require_once 'bootstrap.php';

omifk_main_loop();