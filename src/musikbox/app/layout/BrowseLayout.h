//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007-2016 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cursespp/LayoutBase.h>
#include <cursespp/TextLabel.h>

#include <app/window/CategoryListView.h>
#include <app/window/TrackListView.h>
#include <app/window/TransportWindow.h>
#include <core/audio/PlaybackService.h>

#include <core/library/ILibrary.h>

#include <sigslot/sigslot.h>

namespace musik {
    namespace box {
        class BrowseLayout :
            public cursespp::LayoutBase,
#if (__clang_major__ == 7 && __clang_minor__ == 3)
            public std::enable_shared_from_this<BrowseLayout>,
#endif
            public sigslot::has_slots<>
        {
            public:
                BrowseLayout(
                    musik::core::audio::PlaybackService& playback,
                    musik::core::ILibraryPtr library);

                virtual ~BrowseLayout();

                virtual void OnVisibilityChanged(bool visible);
                virtual cursespp::IWindowPtr GetFocus();
                virtual bool KeyPress(const std::string& key);
                virtual void ProcessMessage(musik::core::runtime::IMessage &message);
                void ScrollTo(const std::string& fieldType, int64_t fieldId);

            protected:
                virtual void OnLayout();

            private:
                void InitializeWindows();

                void SwitchCategory(const std::string& fieldName);

                void OnIndexerProgress(int count);
                void RequeryTrackList(cursespp::ListWindow *view);

                void OnCategoryViewSelectionChanged(
                    cursespp::ListWindow *view, size_t newIndex, size_t oldIndex);

                void OnCategoryViewInvalidated(
                    cursespp::ListWindow *view, size_t selectedIndex);

                bool BrowseLayout::ProcessEditOperation(const std::string& key);

                musik::core::audio::PlaybackService& playback;
                musik::core::ILibraryPtr library;
                std::shared_ptr<CategoryListView> categoryList;
                std::shared_ptr<TrackListView> trackList;
                std::shared_ptr<cursespp::TextLabel> categoryTitle;
                std::shared_ptr<cursespp::TextLabel> tracksTitle;
                cursespp::IWindowPtr focused;
        };
    }
}
