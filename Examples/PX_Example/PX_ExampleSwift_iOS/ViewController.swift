//
//  ViewController.swift
//  PX_ExampleSwift_iOS
//
//  Created by Jamaine Obeng on 13/11/2015.
//  Copyright © 2015 LotsAndLess. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    var timer: NSTimer!
    var directoryContents: [String]! = []
    var currentIterator: Int = 0
    
    //
    @IBOutlet weak var leftNavView: PX_SVG_Button!
    @IBOutlet weak var rightNavView: PX_SVG_Button!
    @IBOutlet weak var animatedSVGView: PX_SVG_View!
    
    @IBOutlet weak var Tab1: PX_SVG_Button!
    @IBOutlet weak var Tab2: PX_SVG_Button!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
    }

    override func viewDidAppear(animated: Bool) {
        
        super.viewWillAppear(animated)
    
        self.setSVGs()
        self.getSVGFilesArray()
        
        self.timer = NSTimer.scheduledTimerWithTimeInterval(1.0, target: self, selector: "update", userInfo: nil, repeats: true)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func setSVGs() {
    
        
        self.animatedSVGView.svg = PX_SVG_Image(SVGNamed: "Roundicons-28", inDirectory: "TEST_SVGS")
        
        self.Tab1.normalSVG   = PX_SVG_Image(SVGNamed: "http---icon-park.com-imagefiles-movie_play_red", inDirectory: "TEST_SVGS")
        self.Tab1.selectedSVG = PX_SVG_Image(SVGNamed: "http---icon-park.com-imagefiles-movie_play_gray", inDirectory: "TEST_SVGS")
    }

    func getSVGFilesArray() {
        
        let docsPath = NSBundle.mainBundle().resourcePath! + "/TEST_SVGS"
        let fileManager = NSFileManager.defaultManager()
        
        do {
            self.directoryContents = try fileManager.contentsOfDirectoryAtPath(docsPath)
        } catch {
            print(error)
        }
    }
    
    // must be internal or public.
    func update() {

        let currentFile = self.directoryContents[self.currentIterator]
        let filename = NSString(string: currentFile).stringByDeletingPathExtension
        
        let svg = PX_SVG_Image(SVGNamed: filename, inDirectory: "TEST_SVGS")
        self.animatedSVGView.svg = svg
        
        self.currentIterator++;
        if ( self.currentIterator >= self.directoryContents.count )
        {
            self.currentIterator = 0;
        }
    }
}

