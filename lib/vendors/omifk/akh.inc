<?php

/* vim: set expandtab tabstop=2 shiftwidth=2 softtabstop=2: */

/**
 * Array Key Helper library
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
 * An array key getter
 *
 * Use this when you have one-level array,
 * ie: $arr = array('key1' => 'value1', 'key2' => 'value2');
 *
 * @param array  $array   array from which you want to get data
 * @param string $key     array key you want to extract
 * @param mixed  $default fallback value in case of non-existent key
 *
 * @return
 *   if the passed key of the array exists, return the corresponding value,
 *   else return the default value(if passed); as last resort return null.
 */
function akh_get(array $array, $key, $default = null) {
    return (isset($array[$key])) ? $array[$key] : $default;
}

/**
 * A recursive array key getter
 *
 * Use this when you have multiple-levels array,
 * ie: $arr = array('key1' => array('key3' => array('key4' => 'value4')),
 *                  'key2' => 'value2');
 *
 * @param array $array   array from which you want to get data
 * @param array $key     array containing index path of the key you want
 *                       to extract(ie: array('a', 'b', 'c')
 *                       will point to $array['a']['b']['c'])
 * @param mixed $default fallback value in case of non-existent key
 *
 * @return
 *   if the passed key of the array exists, return the corresponding value,
 *   else return the default value(if passed); as last resort return null.
 */
function akh_get_recursive(array $array, array $key, $default = null) {
    $inner_key = array_shift($key);
    return isset($array[$inner_key]) ?
        (empty($key) ?
            $array[$inner_key] :
            akh_get_recursive($array[$inner_key], $key, $default)) :
        $default;
}

/**
 * An array key setter
 *
 * Use this when you have one-level array,
 * ie: $arr = array('key1' => 'value1', 'key2' => 'value2');
 * 
 * @param array  $array array in which you want to set data
 * @param string $key   array key in which you want to store value
 * @param mixed  $value value you want to set
 *
 * @return
 *   if the key already exists, the old value of the array,
 *   else NULL
 */
function akh_set(array $array, $key, $value = null) {
    $old_value = akh_get($array, $key);
    $array[$key] = $value;
    return $old_value;
}

/**
 * A recursive array key setter
 *
 * Use this when you have multiple-levels array,
 * ie: $arr = array('key1' => array('key3' => array('key4' => 'value4')),
 *                  'key2' => 'value2');
 *
 * @param array &$array array in which you want to set data
 * @param array $key    array containing index path in which you want 
 *                      to store value(ie: array('a', 'b', 'c')
 *                      will point to $array['a']['b']['c'])
 * @param mixed $value  value you want to set
 *
 * @return
 *   if the key already exists, the old value of the array,
 *   else NULL
 */
function akh_set_recursive(array &$array, array $key = array(), $value = null) {
    $old_value = akh_get_recursive($array, $key);
    if (($inner_key = array_shift($key))) {
        if (!isset($array[$inner_key])) {
            $array[$inner_key] = array();
        }
        akh_set_recursive($array[$inner_key], $key, $value);
    } else {
        $array = $value;
    }
    return $old_value;
}