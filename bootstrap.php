<?php

/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * Bootstrap file
 *
 * Define here basic initialization variables and functions
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

define('OMIFK_DIRECTORY_DATA',     OMIFK_APPLICATION_PATH . 'data/');
define('OMIFK_DIRECTORY_DOC',      OMIFK_APPLICATION_PATH . 'doc/');
define('OMIFK_DIRECTORY_EXAMPLES', OMIFK_APPLICATION_PATH . 'examples/');
define('OMIFK_DIRECTORY_TESTS',    OMIFK_APPLICATION_PATH . 'tests/');

// Mandatory directories
define('OMIFK_DIRECTORY_CONFIG',  OMIFK_APPLICATION_PATH . 'config/');
define('OMIFK_DIRECTORY_LIBRARY', OMIFK_APPLICATION_PATH . 'lib/vendors/');
define('OMIFK_DIRECTORY_MODULES', OMIFK_APPLICATION_PATH . 'modules/');

// Fuel compatibility constants
define('APPPATH', OMIFK_APPLICATION_PATH);
define('COREPATH', OMIFK_DIRECTORY_LIBRARY . 'fuel/core/');

// Load library files
require_once OMIFK_DIRECTORY_LIBRARY . 'omifk/akh.inc';
require_once OMIFK_DIRECTORY_LIBRARY . 'omifk/common.inc';
require_once OMIFK_DIRECTORY_LIBRARY . 'omifk/graph.inc';
require_once OMIFK_DIRECTORY_LIBRARY . 'omifk/module.inc';

// Load config files
require_once OMIFK_DIRECTORY_CONFIG  . 'omifk.php';

// Bootstrap the framework DO NOT edit this
require_once COREPATH . 'bootstrap.php';

/**
 * Set the timezone to what you need it to be.
 */
date_default_timezone_set(
  akh_get_recursive(
    $omifk_config, 
    array('date', 'timezone'), 
    'UTC'
  )
);

/**
 * Set the encoding you would like to use.
 */
Fuel::$encoding = 'UTF-8';

Autoloader::add_classes(array(
  // It looks like they forgot redis class
	'Fuel\\Core\\Redis' => COREPATH . 'classes/redis.php',
  'Fuel\\Core\\Redis_Exception' => COREPATH . 'classes/redis/exception.php',
));

// Register the autoloader
Autoloader::register();

// Initialize the framework with the config file.
Fuel::init(include(APPPATH . 'config/config.php'));

/* End of file bootstrap.php */