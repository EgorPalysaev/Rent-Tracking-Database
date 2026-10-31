<?php
$command = ['/home/egor/RenTrack/src/app'];

$spec = [
    0 => ['pipe', 'r'], // input
    1 => ['pipe', 'w'], // output
    2 => ['pipe', 'w'], // errors
];

$process = proc_open($command, $spec, $pipes);

if (!is_resource($process)) {
    die('Could not start the app.');
}

fclose($pipes[0]); // this example sends no input
$output = stream_get_contents($pipes[1]);
fclose($pipes[1]);
$error = stream_get_contents($pipes[2]);
fclose($pipes[2]);

$exitCode = proc_close($process);

echo '<pre>' . htmlspecialchars(
    $exitCode === 0 ? $output : $error,
    ENT_QUOTES | ENT_SUBSTITUTE,
    'UTF-8'
) . '</pre>';

