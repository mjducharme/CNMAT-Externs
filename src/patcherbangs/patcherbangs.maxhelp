{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 100.0, 100.0, 889.0, 742.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "Default Max 7",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 535.0, 105.0, 76.0, 22.0 ],
					"style" : "",
					"text" : "print context"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontsize" : 12.0,
					"id" : "obj-19",
					"linecount" : 110,
					"maxclass" : "o.compose",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 704.0, 116.0, 563.0, 1505.0 ],
					"saved_bundle_data" : [ 35, 98, 117, 110, 100, 108, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, -116, 47, 99, 111, 110, 116, 101, 120, 116, 0, 0, 0, 0, 44, 46, 0, 0, 0, 0, 15, 120, 35, 98, 117, 110, 100, 108, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 102, 105, 108, 101, 118, 101, 114, 115, 105, 111, 110, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 20, 47, 115, 104, 111, 119, 111, 110, 116, 97, 98, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 116, 101, 120, 116, 106, 117, 115, 116, 105, 102, 105, 99, 97, 116, 105, 111, 110, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 115, 116, 121, 108, 101, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 100, 101, 118, 105, 99, 101, 104, 101, 105, 103, 104, 116, 0, 0, 0, 44, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 103, 108, 111, 98, 97, 108, 112, 97, 116, 99, 104, 101, 114, 110, 97, 109, 101, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 110, 101, 119, 118, 105, 101, 119, 100, 105, 115, 97, 98, 108, 101, 100, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 108, 111, 99, 107, 101, 100, 0, 44, 105, 0, 0, 0, 0, 0, -1, 0, 0, 0, 20, 47, 110, 117, 109, 118, 105, 101, 119, 115, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 103, 114, 105, 100, 111, 110, 111, 112, 101, 110, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 98, 103, 99, 111, 117, 110, 116, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112, 47, 115, 97, 118, 101, 102, 105, 108, 101, 112, 97, 116, 104, 0, 0, 0, 44, 115, 0, 0, 77, 97, 99, 105, 110, 116, 111, 115, 104, 32, 72, 68, 58, 47, 85, 115, 101, 114, 115, 47, 114, 47, 68, 111, 99, 117, 109, 101, 110, 116, 115, 47, 100, 101, 118, 45, 108, 105, 98, 47, 67, 78, 77, 65, 84, 45, 69, 120, 116, 101, 114, 110, 115, 47, 115, 114, 99, 47, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 47, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 46, 109, 97, 120, 104, 101, 108, 112, 0, 0, 0, 0, 64, 47, 100, 101, 102, 97, 117, 108, 116, 95, 109, 97, 116, 114, 105, 120, 112, 108, 99, 111, 108, 111, 114, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -32, 0, 0, 0, 0, 0, 0, 63, -20, -52, -52, -52, -52, -52, -51, 63, -32, 0, 0, 0, 0, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 47, 116, 111, 111, 108, 98, 97, 114, 115, 95, 117, 110, 112, 105, 110, 110, 101, 100, 95, 108, 97, 115, 116, 95, 115, 97, 118, 101, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 116, 111, 111, 108, 98, 97, 114, 105, 100, 0, 0, 44, 115, 0, 0, 112, 97, 116, 99, 104, 101, 114, 101, 100, 105, 116, 111, 114, 0, 0, 0, 0, 0, 0, 16, 47, 100, 105, 103, 101, 115, 116, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 99, 111, 108, 111, 114, 50, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -46, -110, -110, 62, 91, -123, 98, 63, -45, -45, -44, 40, 10, -31, 5, 63, -45, 83, 84, 58, -22, -73, -103, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 102, 103, 99, 111, 117, 110, 116, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 19, 0, 0, 0, 28, 47, 100, 101, 102, 97, 117, 108, 116, 102, 111, 99, 117, 115, 98, 111, 120, 0, 0, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 122, 111, 111, 109, 102, 97, 99, 116, 111, 114, 0, 44, 100, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 111, 98, 106, 101, 99, 116, 115, 110, 97, 112, 111, 110, 111, 112, 101, 110, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 24, 47, 105, 110, 108, 101, 116, 105, 110, 115, 101, 116, 0, 44, 100, 0, 0, 64, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 105, 110, 108, 101, 116, 115, 99, 97, 108, 101, 114, 97, 116, 105, 111, 0, 0, 0, 0, 44, 100, 0, 0, 63, -21, 51, 51, 51, 51, 51, 51, 0, 0, 0, 28, 47, 100, 101, 118, 105, 99, 101, 119, 105, 100, 116, 104, 0, 0, 0, 0, 44, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 105, 115, 104, 101, 108, 112, 102, 105, 108, 101, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 110, 111, 101, 100, 105, 116, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 103, 114, 105, 100, 115, 110, 97, 112, 111, 110, 111, 112, 101, 110, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 98, 111, 116, 116, 111, 109, 116, 111, 111, 108, 98, 97, 114, 112, 105, 110, 110, 101, 100, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 47, 115, 101, 108, 101, 99, 116, 105, 111, 110, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -22, 26, 26, 26, 26, 26, 26, 63, -21, 123, 123, 123, 123, 123, 123, 63, -42, 86, 86, 86, 86, 86, 86, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 99, 111, 108, 111, 114, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -46, -110, -110, 62, 91, -123, 98, 63, -45, -45, -44, 40, 10, -31, 5, 63, -45, 83, 84, 58, -22, -73, -103, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 100, 101, 102, 97, 117, 108, 116, 95, 115, 105, 103, 112, 108, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -21, 83, -9, -50, -39, 22, -121, 63, -16, 0, 0, 0, 0, 0, 0, 63, -32, 114, -80, 32, -60, -101, -90, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 47, 115, 117, 98, 112, 97, 116, 99, 104, 101, 114, 95, 116, 101, 109, 112, 108, 97, 116, 101, 0, 0, 0, 0, 44, 115, 0, 0, 68, 101, 102, 97, 117, 108, 116, 32, 77, 97, 120, 32, 55, 0, 0, 0, 0, 0, 0, 16, 47, 100, 105, 114, 116, 121, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 102, 105, 108, 101, 116, 121, 112, 101, 0, 0, 0, 44, 115, 0, 0, 74, 83, 79, 78, 0, 0, 0, 0, 0, 0, 0, 20, 47, 102, 111, 110, 116, 102, 97, 99, 101, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 97, 98, 115, 116, 114, 97, 99, 116, 105, 111, 110, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 1, 0, 0, 0, 0, 24, 47, 102, 111, 110, 116, 115, 105, 122, 101, 0, 0, 0, 44, 100, 0, 0, 64, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 112, 97, 114, 101, 110, 116, 115, 116, 121, 108, 101, 0, 0, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 47, 99, 111, 108, 111, 114, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -23, -71, -71, -71, -71, -71, -70, 63, -20, -68, -68, -68, -68, -68, -67, 63, -19, 29, 29, 29, 29, 29, 29, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 99, 108, 97, 115, 115, 110, 97, 109, 101, 115, 112, 97, 99, 101, 0, 44, 115, 0, 0, 98, 111, 120, 0, 0, 0, 0, 20, 47, 112, 97, 114, 101, 110, 116, 99, 108, 97, 115, 115, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 28, 47, 119, 111, 114, 107, 115, 112, 97, 99, 101, 100, 105, 115, 97, 98, 108, 101, 100, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 110, 117, 109, 119, 105, 110, 100, 111, 119, 118, 105, 101, 119, 115, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 47, 108, 111, 99, 107, 101, 100, 95, 105, 111, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -36, -52, -52, -52, -52, -52, -51, 63, -36, -52, -52, -52, -52, -52, -51, 63, -36, -52, -52, -52, -52, -52, -51, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 103, 114, 105, 100, 115, 105, 122, 101, 0, 0, 0, 44, 100, 100, 0, 64, 46, 0, 0, 0, 0, 0, 0, 64, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 114, 105, 103, 104, 116, 116, 111, 111, 108, 98, 97, 114, 112, 105, 110, 110, 101, 100, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 112, 114, 101, 115, 101, 110, 116, 97, 116, 105, 111, 110, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 101, 100, 105, 116, 105, 110, 103, 95, 98, 103, 99, 111, 108, 111, 114, 0, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -20, 40, -11, -62, -113, 92, 41, 63, -20, 40, -11, -62, -113, 92, 41, 63, -21, -123, 30, -72, 81, -21, -123, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 108, 47, 102, 105, 108, 101, 112, 97, 116, 104, 0, 0, 0, 44, 115, 0, 0, 77, 97, 99, 105, 110, 116, 111, 115, 104, 32, 72, 68, 58, 47, 85, 115, 101, 114, 115, 47, 114, 47, 68, 111, 99, 117, 109, 101, 110, 116, 115, 47, 100, 101, 118, 45, 108, 105, 98, 47, 67, 78, 77, 65, 84, 45, 69, 120, 116, 101, 114, 110, 115, 47, 115, 114, 99, 47, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 47, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 46, 109, 97, 120, 104, 101, 108, 112, 0, 0, 0, 0, 48, 47, 114, 101, 99, 116, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 64, 89, 0, 0, 0, 0, 0, 0, 64, 89, 0, 0, 0, 0, 0, 0, 64, -117, -56, 0, 0, 0, 0, 0, 64, -121, 48, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 100, 101, 102, 97, 117, 108, 116, 95, 112, 108, 99, 111, 108, 111, 114, 0, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 116, 97, 108, 108, 110, 101, 119, 111, 98, 106, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 97, 110, 103, 108, 101, 0, 0, 44, 100, 0, 0, 64, 112, -32, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 105, 109, 112, 111, 114, 116, 105, 110, 103, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 101, 110, 97, 98, 108, 101, 118, 115, 99, 114, 111, 108, 108, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 24, 47, 102, 111, 110, 116, 110, 97, 109, 101, 0, 0, 0, 44, 115, 0, 0, 65, 114, 105, 97, 108, 0, 0, 0, 0, 0, 0, 88, 47, 112, 97, 116, 104, 110, 97, 109, 101, 0, 0, 0, 44, 115, 0, 0, 77, 97, 99, 105, 110, 116, 111, 115, 104, 32, 72, 68, 58, 47, 85, 115, 101, 114, 115, 47, 114, 47, 68, 111, 99, 117, 109, 101, 110, 116, 115, 47, 100, 101, 118, 45, 108, 105, 98, 47, 67, 78, 77, 65, 84, 45, 69, 120, 116, 101, 114, 110, 115, 47, 115, 114, 99, 47, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 0, 0, 0, 0, 0, 20, 47, 99, 97, 110, 115, 97, 118, 101, 0, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 56, 47, 108, 111, 99, 107, 101, 100, 95, 98, 103, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -20, 40, -11, -62, -113, 92, 41, 63, -20, 40, -11, -62, -113, 92, 41, 63, -21, -123, 30, -72, 81, -21, -123, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 99, 111, 117, 110, 116, 0, 0, 44, 105, 0, 0, 0, 0, 0, 19, 0, 0, 0, 16, 47, 118, 111, 108, 0, 0, 0, 0, 44, 105, 0, 0, -1, -1, -5, 74, 0, 0, 0, 24, 47, 105, 115, 111, 108, 97, 116, 101, 97, 117, 100, 105, 111, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 109, 97, 120, 99, 108, 97, 115, 115, 0, 0, 0, 44, 115, 0, 0, 106, 112, 97, 116, 99, 104, 101, 114, 0, 0, 0, 0, 0, 0, 0, 28, 47, 108, 101, 102, 116, 116, 111, 111, 108, 98, 97, 114, 112, 105, 110, 110, 101, 100, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 47, 111, 112, 101, 110, 114, 101, 99, 116, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 108, 111, 99, 107, 101, 100, 101, 100, 105, 116, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 47, 116, 111, 112, 116, 111, 111, 108, 98, 97, 114, 112, 105, 110, 110, 101, 100, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 116, 97, 103, 115, 0, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 47, 116, 101, 120, 116, 99, 111, 108, 111, 114, 95, 105, 110, 118, 101, 114, 115, 101, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -19, 125, 125, 125, 125, 125, 125, 63, -19, 93, 93, 93, 93, 93, 93, 63, -19, -35, -35, -35, -35, -35, -34, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 47, 98, 103, 99, 111, 108, 111, 114, 0, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -46, -110, -110, -110, -110, -110, -109, 63, -45, -45, -45, -45, -45, -45, -44, 63, -45, 83, 83, 83, 83, 83, 83, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 47, 112, 97, 116, 99, 104, 108, 105, 110, 101, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -28, -52, -52, -52, -52, -52, -51, 63, -28, -52, -52, -52, -52, -52, -51, 63, -28, -52, -52, -52, -52, -52, -51, 63, -20, -52, -52, -52, -52, -52, -51, 0, 0, 0, 52, 47, 98, 111, 103, 117, 115, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -25, 92, 40, -11, -62, -113, 92, 63, -29, -41, 10, 61, 112, -93, -41, 63, -32, -93, -41, 10, 61, 112, -92, 63, -42, 102, 102, 102, 102, 102, 102, 0, 0, 0, 60, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 99, 111, 108, 111, 114, 49, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -40, 24, 25, -46, 57, 29, 88, 63, -40, -104, -103, -65, 89, 70, -61, 63, -39, -103, -103, -103, -103, -103, -102, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 47, 110, 97, 109, 101, 0, 0, 0, 44, 115, 0, 0, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 46, 109, 97, 120, 104, 101, 108, 112, 0, 0, 0, 0, 0, 0, 0, 28, 47, 115, 97, 118, 101, 95, 102, 114, 111, 122, 101, 110, 95, 116, 101, 120, 116, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 52, 47, 116, 101, 120, 116, 99, 111, 108, 111, 114, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 101, 110, 97, 98, 108, 101, 104, 115, 99, 114, 111, 108, 108, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 28, 47, 101, 100, 105, 116, 101, 100, 97, 98, 115, 116, 114, 97, 99, 116, 105, 111, 110, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 98, 111, 120, 97, 110, 105, 109, 97, 116, 101, 116, 105, 109, 101, 0, 44, 105, 0, 0, 0, 0, 0, -56, 0, 0, 0, 40, 47, 102, 105, 108, 101, 110, 97, 109, 101, 0, 0, 0, 44, 115, 0, 0, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 46, 109, 97, 120, 104, 101, 108, 112, 0, 0, 0, 0, 0, 0, 0, 32, 47, 115, 104, 111, 119, 114, 111, 111, 116, 112, 97, 116, 99, 104, 101, 114, 111, 110, 116, 97, 98, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 28, 47, 115, 116, 97, 116, 117, 115, 98, 97, 114, 118, 105, 115, 105, 98, 108, 101, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 2, 0, 0, 0, 28, 47, 111, 112, 101, 110, 105, 110, 112, 114, 101, 115, 101, 110, 116, 97, 116, 105, 111, 110, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 47, 100, 101, 102, 114, 101, 99, 116, 0, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 64, 89, 0, 0, 0, 0, 0, 0, 64, 89, 0, 0, 0, 0, 0, 0, 64, -117, -56, 0, 0, 0, 0, 0, 64, -121, 48, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 115, 104, 111, 119, 99, 112, 117, 117, 115, 97, 103, 101, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 47, 99, 108, 101, 97, 114, 99, 111, 108, 111, 114, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 47, 97, 99, 99, 101, 110, 116, 99, 111, 108, 111, 114, 0, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -33, 95, 95, 95, 95, 95, 95, 63, -33, -33, -33, -33, -33, -33, -32, 63, -32, -112, -112, -112, -112, -112, -111, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 100, 101, 115, 99, 114, 105, 112, 116, 105, 111, 110, 0, 0, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 47, 101, 108, 101, 109, 101, 110, 116, 99, 111, 108, 111, 114, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -40, 24, 24, 24, 24, 24, 24, 63, -40, -104, -104, -104, -104, -104, -103, 63, -39, -103, -103, -103, -103, -103, -102, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 47, 98, 103, 108, 111, 99, 107, 101, 100, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 116, 121, 112, 101, 0, 0, 0, 44, 115, 0, 0, 103, 114, 97, 100, 105, 101, 110, 116, 0, 0, 0, 0, 0, 0, 0, 60, 47, 117, 110, 108, 111, 99, 107, 101, 100, 95, 105, 111, 99, 111, 108, 111, 114, 0, 0, 0, 44, 100, 100, 100, 100, 0, 0, 0, 63, -43, 30, -72, 81, -21, -123, 31, 63, -43, 30, -72, 81, -21, -123, 31, 63, -43, 30, -72, 81, -21, -123, 31, 63, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 47, 116, 105, 116, 108, 101, 0, 0, 44, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 47, 116, 111, 111, 108, 98, 97, 114, 118, 105, 115, 105, 98, 108, 101, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 36, 47, 98, 103, 102, 105, 108, 108, 99, 111, 108, 111, 114, 95, 112, 114, 111, 112, 111, 114, 116, 105, 111, 110, 0, 44, 100, 0, 0, 63, -40, -11, -62, -113, 92, 40, -10, 0, 0, 0, 40, 47, 102, 117, 108, 108, 116, 105, 116, 108, 101, 0, 0, 44, 115, 0, 0, 112, 97, 116, 99, 104, 101, 114, 98, 97, 110, 103, 115, 46, 109, 97, 120, 104, 101, 108, 112, 0, 0, 0, 0, 0, 0, 0, 32, 47, 105, 110, 108, 101, 116, 116, 97, 114, 103, 101, 116, 119, 105, 100, 116, 104, 0, 0, 0, 44, 100, 0, 0, 64, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 47, 97, 114, 103, 117, 109, 101, 110, 116, 115, 0, 0, 44, 105, 115, 115, 115, 115, 115, 115, 115, 115, 115, 0, 0, 0, 3, -21, 35, 49, 0, 0, 35, 50, 0, 0, 35, 51, 0, 0, 35, 52, 0, 0, 35, 53, 0, 0, 35, 54, 0, 0, 35, 55, 0, 0, 35, 56, 0, 0, 35, 57, 0, 0, 0, 0, 0, 24, 47, 115, 110, 97, 112, 115, 104, 111, 116, 118, 97, 108, 105, 100, 0, 0, 44, 105, 0, 0, 0, 0, 0, 1, 0, 0, 0, 20, 47, 97, 117, 116, 111, 115, 97, 118, 101, 0, 0, 0, 44, 105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 47, 112, 97, 114, 101, 110, 116, 0, 44, 46, 0, 0, 0, 0, 0, 16, 35, 98, 117, 110, 100, 108, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0 ],
					"saved_bundle_length" : 4000,
					"text" : "/context : {\n\t/fileversion : 1,\n\t/showontab : 0,\n\t/textjustification : 0,\n\t/style : \"\",\n\t/deviceheight : 0.,\n\t/globalpatchername : \"\",\n\t/newviewdisabled : 0,\n\t/locked : 255,\n\t/numviews : 0,\n\t/gridonopen : 0,\n\t/bgcount : 0,\n\t/savefilepath : \"Macintosh HD:/Users/r/Documents/dev-lib/CNMAT-Externs/src/patcherbangs/patcherbangs.maxhelp\",\n\t/default_matrixplcolor : [0.5, 0.9, 0.5, 1.],\n\t/toolbars_unpinned_last_save : 0,\n\t/toolbarid : \"patchereditor\",\n\t/digest : \"\",\n\t/bgfillcolor_color2 : [0.290196, 0.309804, 0.301961, 1.],\n\t/fgcount : 19,\n\t/defaultfocusbox : \"\",\n\t/zoomfactor : 1.,\n\t/objectsnaponopen : 1,\n\t/inletinset : 6.,\n\t/inletscaleratio : 0.85,\n\t/devicewidth : 0.,\n\t/ishelpfile : 0,\n\t/noedit : 0,\n\t/gridsnaponopen : 0,\n\t/bottomtoolbarpinned : 0,\n\t/selectioncolor : [0.815686, 0.858824, 0.34902, 1.],\n\t/bgfillcolor_color : [0.290196, 0.309804, 0.301961, 1.],\n\t/default_sigplcolor : [0.854, 1., 0.514, 1.],\n\t/subpatcher_template : \"Default Max 7\",\n\t/dirty : 0,\n\t/filetype : \"JSON\",\n\t/fontface : 0,\n\t/abstraction : 256,\n\t/fontsize : 12.,\n\t/parentstyle : \"\",\n\t/color : [0.803922, 0.898039, 0.909804, 1.],\n\t/classnamespace : \"box\",\n\t/parentclass,\n\t/workspacedisabled : 0,\n\t/numwindowviews : 0,\n\t/locked_iocolor : [0.45, 0.45, 0.45, 1.],\n\t/gridsize : [15., 15.],\n\t/righttoolbarpinned : 0,\n\t/presentation : 0,\n\t/editing_bgcolor : [0.88, 0.88, 0.86, 1.],\n\t/filepath : \"Macintosh HD:/Users/r/Documents/dev-lib/CNMAT-Externs/src/patcherbangs/patcherbangs.maxhelp\",\n\t/rect : [100., 100., 889., 742.],\n\t/default_plcolor : [0., 0., 0., 0.],\n\t/tallnewobj : 0,\n\t/bgfillcolor_angle : 270.,\n\t/importing : 0,\n\t/enablevscroll : 1,\n\t/fontname : \"Arial\",\n\t/pathname : \"Macintosh HD:/Users/r/Documents/dev-lib/CNMAT-Externs/src/patcherbangs\",\n\t/cansave : 1,\n\t/locked_bgcolor : [0.88, 0.88, 0.86, 1.],\n\t/count : 19,\n\t/vol : -1206,\n\t/isolateaudio : 0,\n\t/maxclass : \"jpatcher\",\n\t/lefttoolbarpinned : 0,\n\t/openrect : [0., 0., 0., 0.],\n\t/lockededit : 0,\n\t/toptoolbarpinned : 0,\n\t/tags : \"\",\n\t/textcolor_inverse : [0.921569, 0.917647, 0.933333, 1.],\n\t/bgcolor : [0.290196, 0.309804, 0.301961, 1.],\n\t/patchlinecolor : [0.65, 0.65, 0.65, 0.9],\n\t/boguscolor : [0.73, 0.62, 0.52, 0.35],\n\t/bgfillcolor_color1 : [0.376471, 0.384314, 0.4, 1.],\n\t/name : \"patcherbangs.maxhelp\",\n\t/save_frozen_text : 1,\n\t/textcolor : [0., 0., 0., 1.],\n\t/enablehscroll : 1,\n\t/editedabstraction : 0,\n\t/boxanimatetime : 200,\n\t/filename : \"patcherbangs.maxhelp\",\n\t/showrootpatcherontab : 1,\n\t/statusbarvisible : 2,\n\t/openinpresentation : 0,\n\t/defrect : [100., 100., 889., 742.],\n\t/showcpuusage : 0,\n\t/clearcolor : [1., 1., 1., 0.],\n\t/accentcolor : [0.490196, 0.498039, 0.517647, 1.],\n\t/description : \"\",\n\t/elementcolor : [0.376471, 0.384314, 0.4, 1.],\n\t/bglocked : 0,\n\t/bgfillcolor_type : \"gradient\",\n\t/unlocked_iocolor : [0.33, 0.33, 0.33, 1.],\n\t/title : \"\",\n\t/toolbarvisible : 1,\n\t/bgfillcolor_proportion : 0.39,\n\t/fulltitle : \"patcherbangs.maxhelp\",\n\t/inlettargetwidth : 7.,\n\t/arguments : [1003, \"#1\", \"#2\", \"#3\", \"#4\", \"#5\", \"#6\", \"#7\", \"#8\", \"#9\"],\n\t/snapshotvalid : 1,\n\t/autosave : 0,\n\t/parent : {\n\n\t}\n}"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "FullPacket" ],
					"patching_rect" : [ 535.0, 58.0, 59.0, 22.0 ],
					"style" : "",
					"text" : "o.context"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 128.0, 112.0, 89.0, 22.0 ],
					"style" : "",
					"text" : "print loadmess"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 128.0, 80.0, 100.0, 22.0 ],
					"style" : "",
					"text" : "loadmess #1 #2 "
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 183.0, 183.0, 38.0, 35.0 ],
					"style" : "",
					"text" : "print attrs"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 128.0, 183.0, 38.0, 35.0 ],
					"style" : "",
					"text" : "print args"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 128.0, 150.0, 74.0, 22.0 ],
					"style" : "",
					"text" : "patcherargs"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 326.5, 105.0, 53.0, 22.0 ],
					"style" : "",
					"text" : "print gui"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "FullPacket" ],
					"patching_rect" : [ 326.5, 67.0, 73.0, 22.0 ],
					"style" : "",
					"text" : "o.gui.attach"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 472.0, 311.0, 148.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_parameter"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 558.0, 267.0, 117.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_start"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 433.5, 369.0, 117.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_pattr"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 376.5, 407.0, 133.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_internal"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 324.5, 445.0, 143.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 262.5, 474.0, 113.0, 22.0 ],
					"style" : "",
					"text" : "print loadbang_end"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 203.0, 517.0, 157.0, 22.0 ],
					"style" : "",
					"text" : "print after snapshot restore"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 116.0, 330.0, 75.0, 22.0 ],
					"style" : "",
					"text" : "print willfree"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 64.0, 299.0, 58.0, 22.0 ],
					"style" : "",
					"text" : "print free"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 9,
					"outlettype" : [ "bang", "bang", "bang", "bang", "bang", "bang", "bang", "bang", "bang" ],
					"patching_rect" : [ 311.5, 148.0, 103.0, 22.0 ],
					"style" : "",
					"text" : "patcherbangs"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"order" : 0,
					"source" : [ "obj-1", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-1", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"order" : 1,
					"source" : [ "obj-1", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"order" : 0,
					"source" : [ "obj-1", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-1", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-1", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-1", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"order" : 1,
					"source" : [ "obj-1", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"source" : [ "obj-13", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 1 ],
					"order" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"order" : 1,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "patcherbangs.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.gui.attach.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.context.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.compose.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0,
		"bgfillcolor_type" : "gradient",
		"bgfillcolor_color1" : [ 0.376471, 0.384314, 0.4, 1.0 ],
		"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
		"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
		"bgfillcolor_angle" : 270.0,
		"bgfillcolor_proportion" : 0.39
	}

}
