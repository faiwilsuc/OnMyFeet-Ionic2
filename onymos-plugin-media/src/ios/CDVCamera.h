/*
 * Copyright 2015-2017 Onymos Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLLocationManager.h>
#import <Cordova/CDVPlugin.h>
#import <AVFoundation/AVFoundation.h>
#import <AssetsLibrary/ALAssetsLibrary.h>
#import <MediaPlayer/MediaPlayer.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <Cordova/CDVPlugin.h>
#import "CDVFile.h"
#import <Cordova/CDV.h>

enum CDVDestinationType {
  DestinationTypeDataUrl = 0,
  DestinationTypeFileUri,
  DestinationTypeNativeUri
};
typedef NSUInteger CDVDestinationType;

enum CDVEncodingType {
  EncodingTypeJPEG = 0,
  EncodingTypePNG
};
typedef NSUInteger CDVEncodingType;

enum CDVMediaType {
  MediaTypePicture = 0,
  MediaTypeVideo,
  MediaTypeAll
};
typedef NSUInteger CDVMediaType;

enum CDVQualityType {
  HighQuality = 0,
  MediumQuality = 1,
  LowQuality = 2,
};
typedef NSUInteger CDVQualityType;

enum CDVOutputFileType {
  M4V = 0,
  MPEG4 = 1,
  M4A = 2,
  QUICK_TIME = 3
};
typedef NSUInteger CDVOutputFileType;

enum CDVCaptureError {
  CAPTURE_INTERNAL_ERR = 0,
  CAPTURE_APPLICATION_BUSY = 1,
  CAPTURE_INVALID_ARGUMENT = 2,
  CAPTURE_NO_MEDIA_FILES = 3,
  CAPTURE_NOT_SUPPORTED = 20
};
typedef NSUInteger CDVCaptureError;

@interface CDVPictureOptions : NSObject

@property (strong) NSNumber* quality;
@property (assign) CDVDestinationType destinationType;
@property (assign) UIImagePickerControllerSourceType sourceType;
@property (assign) CGSize targetSize;
@property (assign) CDVEncodingType encodingType;
@property (assign) CDVMediaType mediaType;
@property (assign) BOOL allowsEditing;
@property (assign) BOOL correctOrientation;
@property (assign) BOOL saveToPhotoAlbum;
@property (strong) NSDictionary* popoverOptions;
@property (assign) UIImagePickerControllerCameraDevice cameraDirection;

@property (assign) BOOL popoverSupported;
@property (assign) BOOL usesGeolocation;
@property (assign) BOOL cropToSize;

+ (instancetype) createFromTakePictureArguments:(CDVInvokedUrlCommand*)command;

@end

@interface CDVCameraPicker : UIImagePickerController

@property (strong) CDVPictureOptions* pictureOptions;

@property (copy)   NSString* callbackId;
@property (copy)   NSString* postUrl;
@property (strong) UIPopoverController* pickerPopoverController;
@property (assign) BOOL cropToSize;
@property (strong) UIView* webView;

+ (instancetype) createFromPictureOptions:(CDVPictureOptions*)options;

@end

// ======================================================================= //

@interface CDVImagePicker : UIImagePickerController
{
  NSString* callbackid;
  NSInteger quality;
  NSString* mimeType;
}

@property (assign) NSInteger quality;
@property (copy)   NSString* callbackId;
@property (copy)   NSString* mimeType;

@end

@interface CDVCamera : CDVPlugin <UIImagePickerControllerDelegate,
                       UINavigationControllerDelegate,
                       UIPopoverControllerDelegate,
                       CLLocationManagerDelegate>
{
  CDVImagePicker* pickerImageController;
}

@property (strong) CDVCameraPicker* pickerController;
@property (strong) NSMutableDictionary *metadata;
@property (strong, nonatomic) CLLocationManager *locationManager;
@property (strong) NSData* data;

/*
 * getPicture
 *
 * arguments:
 *	1: this is the javascript function that will be called with the results, the first parameter passed to the
 *		javascript function is the picture as a Base64 encoded string
 *  2: this is the javascript function to be called if there was an error
 * options:
 *	quality: integer between 1 and 100
 */
- (void)takePicture:(CDVInvokedUrlCommand*)command;
- (void)cleanup:(CDVInvokedUrlCommand*)command;
- (void)repositionPopover:(CDVInvokedUrlCommand*)command;
- (void)createThumbnail:(CDVInvokedUrlCommand*)command;
- (void)transcodeVideo:(CDVInvokedUrlCommand*)command;
- (void)runAsBackground:(CDVInvokedUrlCommand*)command;
- (void)getApplicationName:(CDVInvokedUrlCommand*)command;
- (void)getApplicationKey:(CDVInvokedUrlCommand*)command;
- (void)getApplicationTimestamp:(CDVInvokedUrlCommand*)command;
- (void)captureVideo:(CDVInvokedUrlCommand*)command;
- (NSDictionary*)getMediaDictionaryFromPath:(NSString*)fullPath ofType:(NSString*)type;

- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary*)info;
- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingImage:(UIImage*)image editingInfo:(NSDictionary*)editingInfo;
- (void)imagePickerControllerDidCancel:(UIImagePickerController*)picker;
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated;

- (void)locationManager:(CLLocationManager*)manager didUpdateToLocation:(CLLocation*)newLocation fromLocation:(CLLocation*)oldLocation;
- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error;

@end
