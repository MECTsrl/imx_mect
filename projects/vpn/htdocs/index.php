<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html lang="en">

<head>
    <meta charset="UTF-8" />
    <title>TPAC remote log monitoring demo | MECT s.r.l.</title>
    <link href="css/jquery-ui.css" rel="stylesheet" />
</head>

<body>
    <script type="text/javascript" src="js/jquery-1.8.2.js"></script>
    <script type="text/javascript" src="js/jquery-ui.js"></script>
    <script type="text/javascript" src="js/jquery.flot.js"></script>
    <script type="text/javascript" src="js/jquery.flot.time.js"></script>
    <script type="text/javascript" src="js/jquery.flot.navigate.js"></script>

    <?php 
        date_default_timezone_set('Europe/Rome');

        define('DATADIR', 'store');
        define('LOGEXT', '.log');

        $filenames = glob(DATADIR . '/*' . LOGEXT);
        $header = '';
        $header_n = 0;
        $rows = array();
        $plots = array();

        foreach ($filenames as $filename) {
            if (filesize($filename) == 0)
                continue;   // Nothing to do.

            $file = fopen($filename, 'r');

            if ($file === FALSE) {
                echo "Cannot open log file $filename<br>\n";

                exit(1);
            }

            // Process file header.
            $row = fgetcsv($file, 0, ';');
            if (($row !== FALSE) && ($row !== NULL)) {
                $row = array_map('trim', $row);

                // Check header format.
                if (empty($header)) {
                    if ((count($row) <= 2) || ($row[0] !== 'date') || ($row[1] !== 'time')) {
                        echo "Bad header format in file $filename\n";

                        exit(1);
                    }

                    // Save for later consistency checks.
                    $header = $row;
                    $header_n = count($row);

                    // Collect data for plots.
                    $plots[] = array('java time');
                    foreach ($header as $label)
                        $plots[] = array($label);
                }
                elseif (array_diff($header, $row)) {
                    echo "Bad file format $filename\n";

                    exit(1);
                }
            }
            else {
                echo "Error reading log file $filename<br>\n";

                exit(1);
            }

            // Process file contents.
            while (TRUE) {
                // Skip the header.
                $row = fgetcsv($file, 0, ';');
                if ($row === FALSE)
                    break;

                if ($row === NULL) {
                    echo "Error reading log file $filename<br>\n";

                    exit(1);
                }

                // Consistency check
                if (count($row) !== $header_n) {
                    echo "Bad row format in file $filename\n";

                    exit(1);
                }

                $row = array_map('trim', $row);

                $rows[] = $row;     // Append the new row.

                // Add to plot data.
                for ($i = 0; $i < $header_n; $i++) {
                    if ($i === 0) {
                        $plots[0][] = strtotime(str_replace('/', '-', $row[0]) . " $row[1]") * 1000;

                        continue;
                    }

                    $plots[$i + 1][] = $row[$i];
                }
            }
        }

        foreach ($plots as $p=>$plot) {
            // Skip Java time, date, time.
            if ($p < 3)
                continue;

            echo '<div id="plot', $p, '" style="width:600px;height:300px"></div>', "\n";

            echo '<script type="text/javascript">', "\n";
            echo "var data$p = [\n";
            foreach (array_slice($plot, 1) as $i=>$field)
                echo '[', $plots[0][$i + 1], ", $field],\n";
            echo "];\n";
            echo "var series$p = [ {\n";
            echo 'label: "' . $plot[0] . '",' . "\n";
            echo 'lines: { show: true },' . "\n";
            //echo 'points: { show: true },' . "\n";
            echo "data: data$p,\n";
            echo "} ];\n";

            echo 'var plot' . $p . ' = $.plot("#plot' . $p . '", series' . $p . ', ' .
                '{
                    xaxis: { mode: "time" },
                    zoom: { interactive: true },
                    pan: { interactive: true },
                }' .
            ');' . "\n";

            /*
            echo '$(\'<div class="button" style="right:40px;bottom:45px">full view</div>\')
                            .appendTo($("#plot' . $p . '"))
                            .click(function (event) {
                                event.preventDefault();
                                plot' . $p . '.setData(data' . $p . ');
                                plot' . $p . '.setupGrid();
                                plot' . $p . '.draw();
                            });' . "\n";
            */
            echo '</script>', "\n";

            echo '<style type="text/css">', "\n";
            echo '#plot', $p, ' .button { position: absolute; cursor: pointer; }', "\n";
            echo '#plot', $p, ' div.button { font-size: smaller; color: #999; background-color: #eee; padding: 2px; }', "\n";
            echo '</style>', "\n";
        }
    ?>
</body>

</html>
