;-------------------------------------------------------------------------------------
;
;	Read Multiple Detector Image file and fill up the D_IM structure
;
;	Optional input keywords:
;		DATAPATH: Path to the detector image file
;		DFNAME	: Detector image file name
;		PPATH	: Path to the pointing data
;		PFNAME	: Pointing data file name
;		DNAME	: Complete name of detector image file (includes path)
;		PNAME	: Complete name of pointinf data file (includes path)
;
;	NOTE: if all keyword parameters are specified, then DNAME and PNAME override
;		respective path and file name components
;	NOTE: if NOT specified, then hardcoded default values are used.
;
;	version 2.1    26 October 2005
;	Igor Lapshov
;
;-------------------------------------------------------------------------------------

;pro Read_MDImage, DATAPATH=datapath_a, DFNAME=dfname_a, PPATH = ppath_a, PFNAME=pfname_a, DNAME=dname, PNAME=pname
pro Read_MDImage, DATAPATH=datapath_a, DFNAME=dfname_a, PPATH = ppath_a, PFNAME=pfname_a, DNAME=dname, PNAME=pname
;;pro Read_MDImage, DATAPATH=datapath_a, DFNAME=dfname_a, PPATH = '', PFNAME='', DNAME=dname, PNAME=''

COMMON FUNDAMENTALS, LAD_GAP, GAP_START, GAP_END
COMMON DET_IMAGE_OBSERVED, D_IM

LAD_GAP =19

if (keyword_set(datapath_a)) then begin
	dat_p = datapath_a
endif else begin
;	datapath1 = 'sat_axis_+4.6495571_-0.5049813_+0.0000000/'
datapath1 = ''

	;datapath = '/home/lapa/datadisk/grmc/sagile/v0/crab/satellite_on_gc/table_gc/'	; Set this to the path
;	datapath = '/home/lazza/AGILE/SuperAGILE/Imaging/Pipeline_imaging/'	; Set this to the path
	datapath = './'	; Set this to the path
											; where the data is
	dat_p = datapath + datapath1
endelse

if (keyword_set(ppath_a)) then begin
	p_p = ppath_a
endif else begin
	p_p = '/home/lapa/sagile/pointing/'	; Directory to the file with the pointing info
endelse

if (keyword_set(dfname_a)) then begin
	dfname = dfname_a
endif else begin
;	dfname = 'flist_test_'+'f19_agile_for_1E1740.map'			; Complete name of output file
;	dfname = 'flist_test_'+'f19_agile.map'			; Complete name of output file
;	dfname = 'flist_'+'f19_agile_059.map'			; Complete name of output file
;	dfname = 'flist_test_ST_Check_f19_agile.map'
	dfname = 'test.dat'

endelse

if (keyword_set(pfname_a)) then begin
	pfname = pfname_a
endif else begin
	pfname = 'p_info_0.bin'			; Name of the file with the pointing info.
endelse

if (keyword_set(dname)) then begin
	fin = dname
endif else begin
	fin = dat_p+dfname			; Complete name of output file
endelse

if (keyword_set(pname)) then begin
	fin_p = pname
endif else begin
	fin_p	= p_p+pfname
endelse



; Read detector images from the FIN file

Nchan 		= 0			; Number of strips in the detector image

close, 3
openr, 3, fin, /BINARY, ERROR=err

if (err NE 0) then begin
	print, 'READ_MDIMAGE: Unable to open file: ', fin
	goto, exit
endif

fn_length_0 = 0
fn_length_1 = 0
fn_length_2 = 0

hdr = string('a', format='(a55)')
readu, 3, hdr
print, 'hdr = ', hdr
readu, 3, fn_length_1
print, 'first string length = ', fn_length_1

fin_out_file = strarr(fn_length_1+2)
fin_out_file[*] = ' '
readu, 3, fin_out_file
fin_in_this = strjoin(fin_out_file, /SINGLE)
fin_out_file_1 = strcompress(string(fin_in_this, /print), /remove_all)
print, 'fin_out_file_1 ', fin_out_file_1
readu, 3, fn_length_2
print, 'second string length = ', fn_length_2

fin_out_file = strarr(fn_length_2+2)
fin_out_file[*] = ' '
readu, 3, fin_out_file
fin_in_this = strjoin(fin_out_file, /SINGLE)
fin_out_file_2 = strcompress(string(fin_in_this, /print), /remove_all)
print, 'fin_out_file_2 ' ,fin_out_file_2

readu, 3, Nchan
print, 'Nchan = ', Nchan
Tburst 	= 0.
EnMin 	= 0.
EnMax	= 0.
readu, 3, Tburst, EnMin, EnMax
print, 'Tburst = ' , Tburst
print, 'EnMin = ' , EnMin
print, 'EnMax = ' , EnMax



N_regions	= 0
readu, 3, N_regions
print, 'N_regions = ' ,N_regions

maxangle	= 0.
f_length	= 0.
s_width		= 0.
delta_norm	= 0.
readu, 3, maxangle, f_length, s_width, delta_norm
print, 'maxangle = ', maxangle
print, 'f_length = ', f_length
print, 's_width = ', s_width
print, 'delta_norm = ', delta_norm

C_Angles 	= fltarr(N_regions)	; Centers of correction regions
C_Coeffs	= fltarr(N_regions)	; Correction coefficients
readu, 3, C_Angles
readu, 3, C_Coeffs

;i = 0
;while (i lt N_regions) do begin
;  print, 'C_Angles ', i ,C_Angles[i], '        C_Coeffs ', i ,C_Coeffs[i]
;  i = i+1
;endwhile

Hist_Size	= 0
readu, 3, Hist_Size
print, 'Hist_Size = ', Hist_Size

Point_Hist_x	= fltarr(Hist_Size)				; Pointing error histogram for X
Point_Hist_z	= fltarr(Hist_Size)				; Pointing error histogram for Z

readu, 3, Point_Hist_x

readu, 3, Point_Hist_z

;i=0
;while (i lt Hist_Size) do begin
;	print, 'Point_Hist_x ', i , Point_Hist_x[i], '        Point_Hist_z ', i , Point_Hist_z[i]
;	i = i+1
;endwhile

D_Seq		= intarr(4)					; Detector sequence in the output map.
readu, 3, D_Seq
print, 'D_Seq = ', D_Seq



ind		= 0

DetImage 	= lonarr(N_regions, 4, Nchan+LAD_GAP)		; Container of 4 detector images

bbuf = lonarr(Nchan)


k = 0
while (k lt N_regions) do begin ; for each sky region
	readu, 3, ind ; read the index
	print, 'index of sky region ', ind
	print
	print, '### reading d0 data ', ind
	readu, 3, bbuf
	i=0
	while (i lt Nchan) do begin
		print, '	d0 sky reg = ', ind, ' det = ', D_Seq[0], ' 	strip = ', i, ' value = ', bbuf[i]
		i = i+1
	endwhile
	if(Nchan GE 1536) then begin
		DetImage[ind, D_Seq[0],0:767]		=	bbuf[0:767]
		DetImage[ind, D_Seq[0],768:786]		=	0.
		DetImage[ind, D_Seq[0],787:1554]	=	bbuf[768:1535]
	endif
	print, '### ended d0 data ', ind
	print
	print, '### reading d1 data ', ind
	readu, 3, bbuf
	i=0
	while (i lt Nchan) do begin
		print, '	d1 sky reg = ', ind, ' det = ', D_Seq[1], ' 	strip = ', i, ' value = ', bbuf[i]
		i = i+1
	endwhile
	if(Nchan GE 1536) then begin
		DetImage[ind, D_Seq[1],0:767]		=	bbuf[0:767]
		DetImage[ind, D_Seq[1],768:786]		=	0.
		DetImage[ind, D_Seq[1],787:1554]	=	bbuf[768:1535]
	endif
	print, '### ended d1 data ', ind
	print
	print, '### reading d2 data ', ind
 	readu, 3, bbuf
	i=0
	while (i lt Nchan) do begin
		print, '	d2 sky reg = ', ind, ' det = ', D_Seq[2], ' 	strip = ', i, ' value = ', bbuf[i]
		i = i+1
	endwhile
	if(Nchan GE 1536) then begin
		DetImage[ind, D_Seq[2],0:767]		=	bbuf[0:767]
		DetImage[ind, D_Seq[2],768:786]		=	0.
		DetImage[ind, D_Seq[2],787:1554]	=	bbuf[768:1535]
	endif
	print, '### ended d2 data ', ind
	print
	print, '### reading d3 data ', ind
	readu, 3, bbuf
	i=0
	while (i lt Nchan) do begin
		print, '	d3 sky reg = ', ind, ' det = ', D_Seq[3], ' 	strip = ', i, ' value = ', bbuf[i]
		i = i+1
	endwhile
	if(Nchan GE 1536) then begin
		DetImage[ind, D_Seq[3],0:767]		=	bbuf[0:767]
		DetImage[ind, D_Seq[3],768:786]		=	0.
		DetImage[ind, D_Seq[3],787:1554]	=	bbuf[768:1535]
	endif
	print, '### ended d3 data ', ind


k = k+1
endwhile; close the loop on the sky regions
close, 3

D_IM = {DETECTORIMAGE, DETIMAGE:DetImage, N_REGIONS:N_regions, HDR:hdr, NCHAN:Nchan, DFILE:fin_out_file_1,  $
	PFILE:fin_out_file_2, TBURST:Tburst, ENMIN:EnMin, ENMAX:EnMax, MAXANGLE:maxangle, F_LENGTH:f_length,  $
	S_WIDTH:s_width, DELTA_NORM:delta_norm, C_ANGLES:C_Angles, C_COEFFS:C_Coeffs, HIST_SIZE:Hist_Size, $
	POINT_HIST_X:Point_Hist_x, POINT_HIST_Z:Point_Hist_Z, D_SEQ:D_Seq}

print, 'READ_MDIMAGE: Detector image loaded, arrays filled up.'

print, D_IM.N_regions
print, D_IM.DetImage


exit:

end

