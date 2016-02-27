#ifndef VCF_UTIL_H
#define VCF_UTIL_H

#include "htslib/vcf.h"
#include "htslib/sam.h"
#include "logging_util.h"

#define check_vcf_open(path, fp, header) \
	do {\
		if((fp = vcf_open(path, "r")) == NULL) {\
			LOG_EXIT("Could not open input [bv]cf %s. Abort!\n", path);\
		}\
		if((header = vcf_hdr_read(fp)) == NULL) {\
			LOG_EXIT("Could not read header from input [bv]cf %s. Abort!\n", path);\
		}\
	} while(0)

void bcf_add_bam_contigs(bcf_hdr_t *hdr, bam_hdr_t *src);


#ifdef __cplusplus
namespace dlib {
	class VcfHandle {
		const int is_write;
		vcfFile *fp;
	public:
		bcf_hdr_t *vh;
		// Open constructor
		VcfHandle(char *vcf_path):
			is_write(0),
			fp(vcf_open(vcf_path, "r")),
			vh(bcf_hdr_read(fp))
		{
			if(!fp || !vh) LOG_EXIT("Could not open vcf file at %s for reading.", vcf_path);
		}

		char *get_fname() {
			return fp->fn;
		}

		VcfHandle(char *vcf_path, bcf_hdr_t *hdr_template, const char *mode):
			is_write(1),
			fp(vcf_open(vcf_path, mode)),
			vh(bcf_hdr_dup(hdr_template))
		{
			if(!fp) LOG_EXIT("Could not open vcf file at %s for writing.", vcf_path);
			bcf_hdr_write(fp, vh);
			// Opens vcf
		}
		~VcfHandle(){
			if(fp) vcf_close(fp);
			if(vh) bcf_hdr_destroy(vh);
		}
		int write(bcf1_t *b) {
#if !NDEBUG
			if(!is_write) {
				LOG_EXIT("Can't write to a vcf that's been opened for reading....\n");
			}
#endif
			return bcf_write(fp, vh, b);
		}
		int read(bcf1_t *b) {
#if !NDEBUG
			if(is_write) {
				LOG_EXIT("Can't read from a vcf that's been opened for writing....\n");
			}
#endif
			return bcf_read(fp, vh, b);
		}
	};
} /* namespace dlib*/
#endif /* ifdef __cplusplus */

#endif /* VCF_UTIL_H */
